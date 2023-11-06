#pragma once

#include <specter/output/color/structure/color_object.h>
#include <specter/output/color/painter/token_scanner.h>



SPECTER_NAMESPACE_BEGIN


class PaintRule;
class Cursor;
class MatchData;


// an object that takes a string source and paints it
// using PaintRules
class Painter
{
public:
	Painter(const Cursor* cursor = nullptr);
	~Painter();


	// paints a source using PaintingRules
	std::string paint(const std::string& source) noexcept;


	void add_rule(PaintRule* constraint) noexcept { rules_.push_back(constraint); }
	void remove_all_rules() noexcept { rules_.clear(); }


	std::vector<PaintRule*>		rules()		const noexcept { return rules_; }
	const Cursor*				cursor()	const noexcept { return cursor_; }

	void attach_cursor(const Cursor& cursor)	noexcept { cursor_ = &cursor; }
	void detach_cursor() 						noexcept { cursor_ = nullptr; }


private:
	void match_rules(MatchData& data) noexcept;


	std::vector<PaintRule*> rules_;

	const Cursor* cursor_;
};


class StopCondition;


// rule sets that checks if a token matches with them
class PaintRule
{
public:
	PaintRule(const ColorString& color, StopCondition* condition = nullptr);
	virtual ~PaintRule();


	// color to be painted if a token matches
	ColorString color;


protected:
	friend class Painter;
	friend class Matcher;


	bool match(MatchData& data) noexcept;

	// paints a token and draws the cursor on it if available
	void paint_token(std::stringstream& stream, MatchData& data, const bool draw_cursor = false) const noexcept;

	
	void process_stop_condition(std::stringstream& stream, MatchData& data) const noexcept;

	
	// checks if a token matches
	virtual bool token_match(MatchData& data) noexcept = 0;

	// called at end of Painter::paint. recommended to put code
	// that ends the painting or sets member properties to default states
	virtual void reload() noexcept {}


	// paints this object in "stream" and draws cursor
	void paint_and_draw_cursor(std::stringstream& stream, const MatchData& data) const noexcept;

	// paints a token character by character. this method is used to draw the cursor without conflict with
	// Painter object painting
	void paint_token_char_by_char(std::stringstream& stream, const MatchData& data, const std::string& token_color) const noexcept;


	// draws the cursor if it is at last rule iteration.
	static bool draw_cursor_if_at_last_rule(MatchData& data) noexcept;
	
	// cursor is in "data.token"?
	static bool cursor_in_token(const MatchData& data) noexcept;


	StopCondition* m_stop_condition = nullptr;
};


SPECTER_NAMESPACE_END