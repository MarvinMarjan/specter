#include <specter/input/istream.h>

#include <algorithm>

#include <specter/output/color/color.h>
#include <specter/output/ostream.h>
#include <specter/output/cli_control.h>
#include <specter/tcattr_manip.h>



void SPECTER_NAMESPACE Cursor::reload() noexcept
{
	pos.index = 0;
	pos.limit = 0;
}


void SPECTER_NAMESPACE Cursor::check_limit() noexcept
{
	if (pos.index > pos.limit)
		pos.index = pos.limit;
}



void SPECTER_NAMESPACE Cursor::draw(std::string& source) const noexcept
{
	draw(source, pos.index);
}


void SPECTER_NAMESPACE Cursor::draw(std::string& source, const size_t index) const noexcept
{
	if (!active)
		return;

	// check if cursor index is beyond source last character
	if (index >= source.size())
	{
		draw_at_end(source);
		return;
	}

	// draw the cursor
	source.insert(index + 1, RESET_ALL);
	source.insert(index, style.color);
}


std::string SPECTER_NAMESPACE Cursor::at_end() const noexcept
{
	if (!active)
		return "";

	std::string at_end_str = "";
	
	at_end_str += style.color;
	at_end_str += style.at_end;
	at_end_str += RESET_ALL;

	return at_end_str;
}




void SPECTER_NAMESPACE InputBuffer::add(const std::string& input) noexcept
{	
	// do not add empty values
	if (input.empty())
		return;

	const_iterator it;

	// input already exists in buffer?
	if ((it = std::find(cbegin(), cend(), input)) != cend())
	{
		// move it to end
		move_to_end(it);
		return;
	}

	// add input
	push_back(input);
	index_++;

	if (size() == 1)
		index_ = 0;
}


void SPECTER_NAMESPACE InputBuffer::move_to_end(const const_iterator& it) noexcept
{
	const std::string value = *it;
	erase(it);
	push_back(value);
}



void SPECTER_NAMESPACE InputBuffer::reset() noexcept
{
	first_interation_ = true;

	if (empty())
	{
		index_ = 0;
		return;
	}

	index_ = size() - 1;
}


void SPECTER_NAMESPACE InputBuffer::increase(const int amount) noexcept
{
	if (first_interation_)
	{
		first_interation_ = false;
		return;
	}

	if ((int)index_ + amount >= size())
		return;

	index_ += amount;
}


void SPECTER_NAMESPACE InputBuffer::decrease(const int amount) noexcept
{
	if (first_interation_)
	{
		first_interation_ = false;
		return;
	}

	if ((int)index_ - amount < 0)
		return;

	index_ -= amount;
}




void SPECTER_NAMESPACE Istream::print_data_without_cursor() noexcept
{
	m_cursor.active = false;

	clear_input();
	print(format());
	
	m_cursor.active = true;
} 


void SPECTER_NAMESPACE Istream::clear_input() noexcept
{
	print(load_cursor_pos());
	print(erase_screen(FromCursorToEnd));
}




SPECTER_NAMESPACE StdIstream::StdIstream()
{
	m_cursor.style.color = clr(142, underline);
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

	// reload the cursor
	m_cursor.reload();

	// reset buffer index
	m_buffer.reset();

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
		m_cursor.check_limit();

		// loads the saved cursor pos and update the screen
		clear_input();

		// prints the data
		print(format());
	}

	// add input to buffer
	m_buffer.add(m_data);

	// prints the data a last time but without
	// the cursor
	print_data_without_cursor();

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

	m_buffer.reset();

	return false;
}



void SPECTER_NAMESPACE StdIstream::process_sub(const char ch) noexcept
{
	switch ((int)ch)
	{
	case (int)EscCode::up_arrow:
		m_buffer.decrease();
		m_data = m_buffer.get_at_index();
		m_cursor.pos.index = m_data.size();
		break;
	
	case (int)EscCode::down_arrow:
		m_buffer.increase();
		m_data = m_buffer.get_at_index();
		m_cursor.pos.index = m_data.size();
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