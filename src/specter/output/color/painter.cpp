#include <specter/output/color/painter.h>

#include <sstream>

#include <specter/output/ostream.h>
#include <specter/input/istream.h>



SPECTER_NAMESPACE Painter::Painter(const Cursor* cursor)
	: cursor_(cursor)
{}


std::string SPECTER_NAMESPACE Painter::paint(const std::string& source)
{
	// "source" is empty, just return it
	if (source.empty())
		return source;

	std::stringstream stream;
	std::string token;

	size_t begin = 0;
	size_t end = 0;

	Painter::MatchData data(token, cursor_, begin, end);

	// if code reachs here, it means "source" is not empty.
	// that way, we can ensure that at least one iteration will occur
	bool at_end = false;

	while (!at_end)
	{
		// set "begin" to "end"
		begin = end;

		// gets the current character and increments "end"
		const char ch = source[end++];

		// update "at_end" condition
		at_end = (end >= source.size());

		// find the last index of a word
		while (is_alphanum(ch) && is_alphanum(source[end]))
			end++;

		// gets the current char/word substring
		token = source.substr(begin, end - begin);
		data.raw_token = token;

		// is at last token iteration?
		data.last_token = at_end;

		// match "token" until a rule matches it
		for (size_t i = 0; i < rules_.size(); i++)
		{
			// is at last rule iteration?
			data.last_rule = (i + 1 >= rules_.size());

			if (rules_[i].match(data))
				break;
		}

		// add to "stream" the matched "token"
		stream << token;
	}

	return stream.str();
}




SPECTER_NAMESPACE PaintingRule::PaintingRule(const std::string& matcher, const ColorString& color)
{
	matcher_ = matcher;
	color_ = color;
}




bool SPECTER_NAMESPACE PaintingRule::match(Painter::MatchData& data) const noexcept
{
	std::stringstream stream;

	// is cursor in current token?
	const bool is_cursor_in_token = cursor_in_token(data);

	if (data.raw_token != matcher_)
	{
		if (is_cursor_in_token && data.last_rule)
		{
			const size_t relative_index = data.cursor->pos.index - data.begin;

			data.cursor->draw(data.token, relative_index);
			data.cursor_drawed = true;
		}

		return false;
	}


	if (is_cursor_in_token)
	{
		paint_and_draw_cursor(stream, data);
		data.cursor_drawed = true;
	}

	else
		stream << color_.get() << data.token << RESET_ALL;


	data.token = stream.str();

	return true;
}



void SPECTER_NAMESPACE PaintingRule::paint_and_draw_cursor(std::stringstream& stream, Painter::MatchData& data) const noexcept
{
	const Cursor* cursor = data.cursor;

	if (!cursor)
		return;

	const std::string token_color = color_.get();
	const std::string cursor_color = cursor->style.color;

	const size_t cursor_index = cursor->pos.index;
	const size_t relative_index = cursor_index - data.begin;


	stream << token_color;

	if (relative_index >= data.raw_token.size())
	{
		stream << data.raw_token;
		stream << cursor->at_end();
	}

	else
		for (size_t i = 0; i < data.raw_token.size(); i++)
		{
			const char token_char = data.raw_token[i];

			if (i == relative_index)
			{
				stream << cursor_color << token_char << token_color;
				continue;
			}

			stream << token_char;
		}

	stream << RESET_ALL;
}



bool SPECTER_NAMESPACE PaintingRule::cursor_in_token(const Painter::MatchData& data) noexcept
{
	if (!data.cursor)
		return false;

	const size_t cursor_index = data.cursor->pos.index;

	if (data.last_token && !data.cursor_drawed)
		return true;

	return (!data.cursor_drawed && cursor_index >= data.begin && cursor_index < data.end);
}