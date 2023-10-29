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

		// a cursor pointer. necessary if you want to have a cursor drawn and 
		// a painting of Painter object in the same string without getting conflicts
		// or an weird result
		const Cursor* cursor;

		const size_t& begin;
		const size_t& end;

		bool cursor_drawed = false;
		bool last_rule = false;
		bool last_token = false;
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

	void paint_and_draw_cursor(std::stringstream& stream, Painter::MatchData& data) const noexcept;


	static bool cursor_in_token(const Painter::MatchData& data) noexcept;


	std::string matcher_;
	ColorString color_;
};


SPECTER_NAMESPACE_END