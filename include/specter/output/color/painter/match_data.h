#pragma once

#include <vector>

#include <specter/output/color/painter/token_scanner.h>



SPECTER_NAMESPACE_BEGIN


class Cursor;
class PaintRule;


class MatchData
{
public:
	MatchData(const std::vector<Token>& tokens, const Cursor* cursor)
		: tokens(tokens), cursor(cursor)
	{
		update_all();
	}


	void next() noexcept;


	std::vector<Token> tokens;

	// current token index
	size_t index() const noexcept { return index_; }


	Token token;


	// a cursor pointer. necessary if you want to have a Cursor drawn and 
	// a painting of Painter object in the same string without getting conflicts
	// or a weird result
	const Cursor* cursor;

	size_t relative_cursor_index()	const noexcept { return relative_cursor_index_; }
	size_t cursor_index()			const noexcept { return cursor_index_; }


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


	// update rule data variable members and return the right rule
	PaintRule* update_rule_data(const std::vector<PaintRule*>& rules, const size_t current_index) noexcept;

	void update_all() noexcept;

	void update_token_data()	noexcept;
	void update_cursor_data()	noexcept;


	size_t index_ = 0;


	size_t cursor_index_;
	
	// cursor index relative to token (0 means the first token character)
	size_t relative_cursor_index_;


	PaintRule* current_rule_ = nullptr;


	size_t offset_ = 0;


	bool last_rule_ = false;
	bool last_token_ = false;
	bool end_reached_ = false;
};


SPECTER_NAMESPACE_END