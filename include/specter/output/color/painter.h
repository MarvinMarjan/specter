#pragma once

#include <vector>

#include <specter/output/color/color_object.h>



SPECTER_NAMESPACE_BEGIN


class PaintingRule;
class Cursor;


class Painter
{
public:
	using RuleList = std::vector<PaintingRule*>;


	struct MatchData
	{
		MatchData(std::string& token, const Cursor* cursor, const size_t& begin, const size_t& end)
			: token(token), cursor(cursor), begin(begin), end(end) {}


		std::string& token;		// token
		std::string raw_token;	// raw token (modifications are held locally; copy value)

		// a cursor pointer. necessary if you want to have a Cursor drawn and 
		// a painting of Painter object in the same string without getting conflicts
		// or a weird result
		const Cursor* cursor;

		const size_t& begin;
		const size_t& end;

		bool cursor_drawn = false;	// cursor has been drawn?
		bool last_rule = false;		// last rule iteration?
		bool last_token = false;	// last token iteration?
	};


	Painter(const Cursor* cursor = nullptr);
	~Painter();


	// paints a source using PaintingRules
	std::string paint(const std::string& source);


	void add_rule(PaintingRule* constraint) noexcept { rules_.push_back(constraint); }
	void remove_all() noexcept { rules_.clear(); }


	RuleList		rules()		const noexcept { return rules_; }
	const Cursor*	cursor()	const noexcept { return cursor_; }

	void attach_cursor(const Cursor& cursor) noexcept { cursor_ = &cursor; }
	void detach_cursor() noexcept { cursor_ = nullptr; }


private:

	void match_rules(Painter::MatchData& data) noexcept;


	RuleList rules_;

	const Cursor* cursor_;
};



class PaintingRule
{
public:
	PaintingRule(const ColorString& color);


	ColorString color;

protected:
	friend class Painter;


	bool match(Painter::MatchData& data);
	void paint_token(std::stringstream& stream, Painter::MatchData& data, const bool draw_cursor = false) const noexcept;
	
	virtual bool token_match(const std::string& token) = 0;
	virtual void reload() noexcept {}


	// paints this object in "stream" and draws cursor
	void paint_and_draw_cursor(std::stringstream& stream, const Painter::MatchData& data) const noexcept;
	void paint_token_char_by_char(std::stringstream& stream, const Painter::MatchData& data, const std::string& token_color) const noexcept;


	// recommended to use raw strings (without any coloring)
	static bool draw_cursor_if_at_last_rule(const Painter::MatchData& data) noexcept;
	
	// cursor is in "data.token"?
	static bool cursor_in_token(const Painter::MatchData& data) noexcept;
};


SPECTER_NAMESPACE_END