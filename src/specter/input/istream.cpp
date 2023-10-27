#include <specter/input/istream.h>

#include <specter/output/color.h>
#include <specter/output/ostream.h>
#include <specter/output/cli_control.h>
#include <specter/tcattr_manip.h>



void SPECTER_NAMESPACE Cursor::draw(std::string& source) const noexcept
{
	// check if cursor index is beyond source last character
	if (pos.index >= source.size())
	{
		draw_at_end(source);
		return;
	}

	// draw the cursor
	source.insert(pos.index + 1, style.color_end);
	source.insert(pos.index, style.color_start);
}


void SPECTER_NAMESPACE Cursor::draw_at_end(std::string& source) const noexcept
{
	source += style.color_start;
	source += style.at_end;
	source += style.color_end;
}



SPECTER_NAMESPACE StdIstream::StdIstream()
{
	m_cursor.style.color_start = clr(142, underline);
	m_cursor.style.color_end = RESET_ALL;
	m_cursor.style.at_end = "_";
}



std::string SPECTER_NAMESPACE StdIstream::read()
{
	// necessary to allow character input without the need of pressing "enter".
	enable_continuous_input();

	// save the current cursor pos and it
	print(save_cursor_pos(), hide_cursor());

	// clear previous data
	m_data.clear();

	char ch = '\0';
	int ch_code = 0;
	
	// get characters until "enter" (linefeed) pressed
	while (ch_code != (int)CharCode::LF)
	{
		ch = getchar();
		ch_code = (int)ch;
		
		// if not a control key
		if (!process(ch))
		{
			m_data.insert(m_data.cbegin() + m_cursor.pos.index, ch);
			m_cursor.pos.index++; // force increment
		}

		// update the cursor limit to the input size
		m_cursor.pos.limit = m_data.size();

		// loads the saved cursor pos and update the screen
		clear_input();

		// prints the data
		print(format());
	}

	// restore default terminal attributes
	set_default_stdin_tcattr();
	println(show_cursor());

	return m_data;
}



bool SPECTER_NAMESPACE StdIstream::process(const char ch) noexcept
{
	switch ((int)ch)
	{
	case (int)CharCode::LF:
		return true;

	case (int)CharCode::ESC: {
		const char esc = getchar();
		const char seq = getchar();

		process_sub(seq);

		return true;
	}

	case (int)CharCode::DEL:
		if (m_data.empty() || !m_cursor.pos.index)
			return true;

		m_data.erase(m_data.cbegin() + m_cursor.pos.index - 1);
		m_cursor.pos--;

		return true;
	}

	return false;
}



void SPECTER_NAMESPACE StdIstream::process_sub(const char ch) noexcept
{
	switch ((int)ch)
	{
	case (int)EscCode::up_arrow:
		break;
	
	case (int)EscCode::down_arrow:
		break;

	case (int)EscCode::left_arrow:
		m_cursor.pos--;
		break;

	case (int)EscCode::right_arrow:
		m_cursor.pos++;
		break;
	}
}



std::string SPECTER_NAMESPACE StdIstream::format() noexcept
{
	std::string formatted = m_data;

	m_cursor.draw(formatted);
	
	return formatted;
}



void SPECTER_NAMESPACE StdIstream::clear_input() noexcept
{
	print(load_cursor_pos());
	print(erase_screen(FromCursorToEnd));
}