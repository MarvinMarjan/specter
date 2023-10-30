#pragma once

#include <vector>

#include <specter/output/color/color_object.h>



SPECTER_NAMESPACE_BEGIN


class PaintingRule;
class Cursor;


class Painter
{
public:
	using RuleList = std::vector<PaintingRule>;


	Painter(const Cursor* cursor = nullptr);


	// paints a source using PaintingRules
	std::string paint(const std::string& source);


	void add_rule(const PaintingRule& constraint) noexcept { rules_.push_back(constraint); }
	void remove_all() noexcept { rules_.clear(); }


	RuleList		rules()		const noexcept { return rules_; }
	const Cursor*	cursor()	const noexcept { return cursor_; }

	void set_cursor(const Cursor* cursor)	noexcept { cursor_ = cursor; }


private:
	friend class PaintingRule;


	struct MatchData
	{
		MatchData(std::string& token, const Cursor* cursor, const size_t& begin, const size_t& end)
			: token(token), cursor(cursor), begin(begin), end(end) {}


		std::string& token;		// token
		std::string raw_token;	// raw token (modifications are held locally; copy value)

		// a cursor pointer. necessary if you want to have a Cursor drawn and 
		// a painting of Painter object in the same string without getting conflicts
		// or an weird result
		const Cursor* cursor;

		const size_t& begin;
		const size_t& end;

		bool cursor_drawn = false;	// cursor has been drawn?
		bool last_rule = false;		// last rule iteration?
		bool last_token = false;	// last token iteration?
	};


	RuleList rules_;

	const Cursor* cursor_;
};



class PaintingRule
{
public:
	PaintingRule(const std::string& matcher, const ColorString& color);


	ColorString color() 	const noexcept { return color_; }
	std::string	matcher()	const noexcept { return matcher_; }


	void set_color(const ColorString& color)		noexcept { color_ = color; }
	void set_matcher(const std::string& matcher)	noexcept { matcher_ = matcher; }


private:
	friend class Painter;


	bool match(Painter::MatchData& data) const noexcept;

	// paints this object in "stream" and draws cursor
	void paint_and_draw_cursor(std::stringstream& stream, const Painter::MatchData& data) const noexcept;


	// recommended to use raw strings (without any coloring)
	static bool draw_cursor_if_at_last_rule(const Painter::MatchData& data) noexcept;
	
	// cursor is in "data.token"?
	static bool cursor_in_token(const Painter::MatchData& data) noexcept;


	std::string matcher_;
	ColorString color_;
};


SPECTER_NAMESPACE_END