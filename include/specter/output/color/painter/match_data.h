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
		: raw_token(token), token(token), index_(index), cursor(cursor)
	{}


	void next() noexcept;
	void update() noexcept;


	std::vector<Token> tokens;

	// current token index
	size_t index() const noexcept { return index_; }


	const Token&	raw_token;	// raw token (modifications are not allowed)
	Token&			token;		// token


	// a cursor pointer. necessary if you want to have a Cursor drawn and 
	// a painting of Painter object in the same string without getting conflicts
	// or a weird result
	const Cursor* cursor;


	// if not nullptr, tokens will always be matched with this rule
	PaintRule* forcing_rule = nullptr;

	
	const PaintRule* current_rule() const noexcept { return current_rule_; }


	// if not zero, the current rule will also match the next n tokens
	size_t offset() const noexcept { return offset_; }


	bool last_rule()	const noexcept { return last_rule_; }	// last rule iteration?
	bool last_token()	const noexcept { return last_token_; }	// last token iteration?
	bool end_reached()	const noexcept { return end_reached_; }	// end of tokens reached?


	bool cursor_drawn = false;	// cursor has been drawn?


private:
	friend class Painter;
	friend class PaintRule;
	friend class Matcher;


	size_t& index_;


	PaintRule* current_rule_ = nullptr;


	size_t offset_ = 0;


	bool last_rule_ = false;
	bool last_token_ = false;
	bool end_reached_ = false;
};


SPECTER_NAMESPACE_END