#pragma once

#include <vector>

#include <specter/output/color/structure/color_object.h>
#include <specter/output/color/painter/token_scanner.h>



SPECTER_NAMESPACE_BEGIN


class PaintRule;
class Cursor;


class Painter
{
public:
	using RuleList = std::vector<PaintRule*>;


	struct MatchData
	{
		MatchData(Token& token, const Cursor* cursor)
			: token(token), cursor(cursor) {}


		Token& token;		// token
		Token raw_token;	// raw token (modifications are held locally; copy value)


		// a cursor pointer. necessary if you want to have a Cursor drawn and 
		// a painting of Painter object in the same string without getting conflicts
		// or a weird result
		const Cursor* cursor;


		// if not nullptr, tokens will always be matched with this rule
		PaintRule* forcing_rule = nullptr;


		bool cursor_drawn = false;	// cursor has been drawn?
		bool last_rule = false;		// last rule iteration?
		bool last_token = false;	// last token iteration?
	};


	Painter(const Cursor* cursor = nullptr);
	~Painter();


	// paints a source using PaintingRules
	std::string paint(const std::string& source) noexcept;


	void add_rule(PaintRule* constraint) noexcept { rules_.push_back(constraint); }
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



class PaintRule
{
public:
	PaintRule(const ColorString& color);
	virtual ~PaintRule() = default;


	ColorString color;


protected:
	friend class Painter;


	bool match(Painter::MatchData& data) noexcept;
	void paint_token(std::stringstream& stream, Painter::MatchData& data, const bool draw_cursor = false) const noexcept;
	
	
	// checks if a token matches
	virtual bool token_match(Painter::MatchData& data) noexcept = 0;

	// called at end of Painter::paint. recommended to put code
	// that ends the painting or sets member properties to default states
	virtual void reload() noexcept {}


	// paints this object in "stream" and draws cursor
	void paint_and_draw_cursor(std::stringstream& stream, const Painter::MatchData& data) const noexcept;

	// paints a token character by character. this method is used to draw the cursor without conflict with
	// Painter object painting
	void paint_token_char_by_char(std::stringstream& stream, const Painter::MatchData& data, const std::string& token_color) const noexcept;


	// draws the cursor if it is at last rule iteration.
	static bool draw_cursor_if_at_last_rule(const Painter::MatchData& data) noexcept;
	
	// cursor is in "data.token"?
	static bool cursor_in_token(const Painter::MatchData& data) noexcept;
};


SPECTER_NAMESPACE_END