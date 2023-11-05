#include <specter/output/color/painter/painter.h>

#include <sstream>

#include <specter/input/istream.h>
#include <specter/output/color/painter/stop_condition.h>
#include <specter/output/color/painter/match_data.h>

#include <specter/output/ostream.h>



SPECTER_NAMESPACE Painter::Painter(const Cursor* cursor)
	: cursor_(cursor)
{}

SPECTER_NAMESPACE Painter::~Painter()
{
	// free all rules memory
	for (size_t i = 0; i < rules_.size(); i++)
		if (rules_[i])
		{
			delete rules_[i];
			rules_[i] = nullptr;
		}
}



std::string SPECTER_NAMESPACE Painter::paint(const std::string& source) noexcept
{
	// "source" is empty, just return it
	if (source.empty())
		return source;

	// there is no rules, try to draw the cursor and return
	if (rules_.empty())
	{
		if (!cursor_)
			return source;
		
		std::string copy = source;
		cursor_->draw(copy);

		return copy;
	}

	const std::vector<Token> tokens = TokenScanner(source).scan();

	std::stringstream stream;

	// object to be passed to functions that
	// provides useful information about current state
	MatchData data(tokens, cursor_);

	// iterate through all tokens and match them
	while (!data.end_reached())
	{
		// match the current token with all rules
		match_rules(data);

		stream << data.token.source;
		
		// advances to the next token
		data.next();
	}

	// reload all rules
	for (PaintRule* rule : rules_)
		if (rule)
			rule->reload();

	return stream.str();
}



void SPECTER_NAMESPACE Painter::match_rules(MatchData& data) noexcept
{
	for (size_t i = 0; i < rules_.size(); i++)
	{
		// get the right rule
		PaintRule* rule = data.update_rule_data(rules_, i);

		if (!rule)
			continue;

		// rule has matched, do not match others
		if (rule->match(data))
			break;
	}
}






SPECTER_NAMESPACE PaintRule::PaintRule(const ColorString& color, StopCondition* condition)
{
	this->color = color;
	m_stop_condition = condition;
}

SPECTER_NAMESPACE PaintRule::~PaintRule()
{
	if (!m_stop_condition)
		return;
		
	delete m_stop_condition;
	m_stop_condition = nullptr;
}



bool SPECTER_NAMESPACE PaintRule::match(MatchData& data) noexcept
{
	// is cursor in current token?
	const bool is_cursor_in_token = cursor_in_token(data);

	// token do not match?
	if (!token_match(data))
	{
		if (is_cursor_in_token && draw_cursor_if_at_last_rule(data))
			data.cursor_drawn = true; // just set this to true if cursor could be drawn
		
		return false;
	}

	// stream where token will be builded
	std::stringstream stream;

	paint_token(stream, data, is_cursor_in_token);

	// modify token.
	// only modify at end to avoid disturbing 
	// other functions that need it raw
	data.token.source = stream.str();

	// reload StopCondition if not nullptr
	if (m_stop_condition)
		m_stop_condition->reload();
	
	return true;
}



void SPECTER_NAMESPACE PaintRule::paint_token(std::stringstream& stream, MatchData& data, const bool draw_cursor) const noexcept
{
	// paints the token and draws the cursor
	if (draw_cursor)
	{
		paint_and_draw_cursor(stream, data);
		data.cursor_drawn = true;
	}

	// no need to draw the cursor, just paint the token
	else
		stream << color.get() << data.token.source << RESET_ALL;
	

	process_stop_condition(stream, data);
}



void SPECTER_NAMESPACE PaintRule::process_stop_condition(std::stringstream& stream, MatchData& data) const noexcept
{
	const bool should_stop = (!m_stop_condition || m_stop_condition->stop());
	const bool zero_offset = !data.offset_;

	if (should_stop && zero_offset)
		return;

	// process stop condition if not nullptr
	if (m_stop_condition)
		m_stop_condition->process(data);

	// decreases offset if not zero
	if (!zero_offset)
		data.offset_--;
	
	// advance to the next token
	data.next();

	// paint the token
	paint_token(stream, data, cursor_in_token(data));
}



void SPECTER_NAMESPACE PaintRule::paint_and_draw_cursor(std::stringstream& stream, const MatchData& data) const noexcept
{
	const Cursor*	cursor = data.cursor;
	const Token&	token = data.token;

	// note: condition below is just for safety purposes, since, by default,
	// this method will not be called if "is_cursor_in_token" (see PaintRule::match)
	// is false (it is false when cursor is a nullptr)

	// there is no cursor to draw?
	if (!cursor)
		return;

	const std::string token_color = color.get();
	const std::string cursor_color = cursor->style.color;


	// start token color
	stream << token_color;

	// is cursor at end of token?
	if (data.relative_cursor_index() >= token.source.size())
	{
		stream << token.source;
		stream << cursor->at_end(); // adds "RESET_ALL" at end. no need to append it again

		return;
	}

	// colorizes token adding character by character.
	// necessary to draw cursor when found it
	paint_token_char_by_char(stream, data, token_color);

	// end token color
	stream << RESET_ALL;
}



void SPECTER_NAMESPACE PaintRule::paint_token_char_by_char(std::stringstream& stream, const MatchData& data, const std::string& token_color) const noexcept
{
	const Cursor*	cursor = data.cursor;
	const Token&	token = data.token;

	if (!cursor)
		return;

	const size_t relative_index = data.relative_cursor_index();

	// paints character by character. also draws the cursor
	for (size_t i = 0; i < token.source.size(); i++)
	{
		const char token_char = token.source[i];

		// is cursor at current character?
		if (i == relative_index)
		{
			stream << cursor->style.color << token_char << token_color;
			continue;
		}

		stream << token_char;
	}
}



bool SPECTER_NAMESPACE PaintRule::draw_cursor_if_at_last_rule(MatchData& data) noexcept
{
	// not at last rule iteration. return
	if (!data.last_rule())
		return false;

	data.cursor->draw(data.token.source, data.relative_cursor_index());

	return true;
}



bool SPECTER_NAMESPACE PaintRule::cursor_in_token(const MatchData& data) noexcept
{
	// nullptr cursor. return false
	if (!data.cursor)
		return false;

	// last token reached but cursor was not drawn,
	// it means that the cursor might be in the current "data.token"
	if (data.last_token() && !data.cursor_drawn)
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

	return (!data.cursor_drawn && data.cursor_index() >= data.token.begin && data.cursor_index() < data.token.end);
}