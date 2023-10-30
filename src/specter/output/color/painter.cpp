#include <specter/output/color/painter.h>

#include <sstream>

#include <specter/output/ostream.h>
#include <specter/input/istream.h>



SPECTER_NAMESPACE Painter::Painter(const Cursor* cursor)
	: cursor_(cursor)
{}

SPECTER_NAMESPACE Painter::~Painter()
{
	for (const PaintingRule* rule : rules_)
		if (rule)
			delete rule;
}


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

		// find the last index of a word token
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
			const PaintingRule* rule = rules_[i];

			if (!rule)
				continue;

			// is at last rule iteration?
			data.last_rule = (i + 1 >= rules_.size());

			// rule has matched, no need to match others
			if (rule->match(data))
				break;
		}

		// add to "stream" the matched "token"
		stream << token;
	}

	return stream.str();
}




SPECTER_NAMESPACE PaintingRule::PaintingRule(const ColorString& color)
{
	this->color = color;
}




bool SPECTER_NAMESPACE PaintingRule::match(Painter::MatchData& data) const noexcept
{
	std::stringstream stream;

	// is cursor in current token?
	const bool is_cursor_in_token = cursor_in_token(data);

	// token do not matchs with this matcher
	if (!token_match(data.raw_token))
	{
		if (is_cursor_in_token && draw_cursor_if_at_last_rule(data))
			data.cursor_drawn = true; // just set this to true if cursor could be drawn
		
		return false;
	}


	if (is_cursor_in_token)
	{
		paint_and_draw_cursor(stream, data);
		data.cursor_drawn = true;
	}

	else
		stream << color.get() << data.token << RESET_ALL;


	// modify token
	data.token = stream.str();

	return true;
}



void SPECTER_NAMESPACE PaintingRule::paint_and_draw_cursor(std::stringstream& stream, const Painter::MatchData& data) const noexcept
{
	const Cursor* cursor = data.cursor;

	// note: condition below is just for safety purposes, since, by default,
	// this method will not be called if "is_cursor_in_token" (see PaintingRule::match)
	// is false (it is false when cursor is a nullptr)

	// there is no cursor to draw?
	if (!cursor)
		return;

	const std::string token_color = color.get();
	const std::string cursor_color = cursor->style.color;

	const size_t cursor_index = cursor->pos.index;
	
	// cursor index relative to token (0 means the first token character)
	const size_t relative_index = cursor_index - data.begin;


	// start token color
	stream << token_color;

	// is cursor at end of token?
	if (relative_index >= data.raw_token.size())
	{
		stream << data.raw_token;
		stream << cursor->at_end(); // adds "RESET_ALL" at end. no need to append it again

		return;
	}

	// colorizes token adding character by character.
	// necessary to draw cursor when found it
	for (size_t i = 0; i < data.raw_token.size(); i++)
	{
		const char token_char = data.raw_token[i];

		// is cursor at current character?
		if (i == relative_index)
		{
			stream << cursor_color << token_char << token_color;
			continue;
		}

		stream << token_char;
	}

	// end token color
	stream << RESET_ALL;
}



bool SPECTER_NAMESPACE PaintingRule::draw_cursor_if_at_last_rule(const Painter::MatchData& data) noexcept
{
	// not at last rule iteration. return
	if (!data.last_rule)
		return false;

	const size_t relative_index = data.cursor->pos.index - data.begin;

	data.cursor->draw(data.token, relative_index);

	return true;
}



bool SPECTER_NAMESPACE PaintingRule::cursor_in_token(const Painter::MatchData& data) noexcept
{
	// nullptr cursor. return false
	if (!data.cursor)
		return false;

	const size_t cursor_index = data.cursor->pos.index;

	// last token reached but cursor was not drawn,
	// it means that the cursor might be in the current "data.token"
	if (data.last_token && !data.cursor_drawn)
		return true;

	// "!data.cursor_drawn":			do not draw cursor twice
	// "cursor_index >= data.begin":	cursor index must be greater/equal to the begin index of "data.token"
	// "cursor_index < data.end":		(see below)
	
	// if it were "cursor_index <= data.end" instead, we would have a problem:
	// "data.end" sometimes have the same "data.begin" value of the next token.
	// for example:

	// "cute panda" - here, there is 3 tokens (blank charactes like ' ' also counts):
	// "cute", " " and "panda".
	
	// "cute":	begin = 0; end = 4 (ends at the blank space)
	// " ":		begin = 4; end = 5 (ends at "p" from "panda")
	// "panda":	begin = 5; end = 9

	// above, we can visualize the problem: the end of "cute" is same as the begin (4)
	// of " ". the end of " " is same as the begin of "panda" (5).
	
	// with that, if we use "<=" instead of "<", the " " (blank space) token would be ignorated
	// even if the cursor is at it (the condition below would consider that cursor is at the "cute" token),
	// causing a weird result.
	
	// swaping "cursor_index >= data.begin" to use ">" and "cursor_index < data.end" to use "<="
	// would also work

	return (!data.cursor_drawn && cursor_index >= data.begin && cursor_index < data.end);
}