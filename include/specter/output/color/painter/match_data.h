#pragma once

#include <vector>

#include <specter/macro.h>



SPECTER_NAMESPACE_BEGIN


class Cursor;
class Token;
class PaintRule;


class MatchData
{
public:
	MatchData(Token& token, size_t index, const Cursor* cursor)
		: raw_token(token), token(token), index(index), cursor(cursor)
	{}


	void next() noexcept;
	void update() noexcept;


	std::vector<Token> tokens;
	size_t& index;


	const Token&	raw_token;	// raw token (modifications are not allowed)
	Token&			token;		// token


	// a cursor pointer. necessary if you want to have a Cursor drawn and 
	// a painting of Painter object in the same string without getting conflicts
	// or a weird result
	const Cursor* cursor;


	// if not nullptr, tokens will always be matched with this rule
	PaintRule* forcing_rule = nullptr;
	PaintRule* current_rule = nullptr;


	size_t offset = 0;


	bool cursor_drawn = false;	// cursor has been drawn?
	bool last_rule = false;		// last rule iteration?
	bool last_token = false;	// last token iteration?
	bool end_reached = false;
};


SPECTER_NAMESPACE_END