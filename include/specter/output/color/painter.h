#pragma once

#include <vector>

#include <specter/output/color/color_object.h>



SPECTER_NAMESPACE_BEGIN


struct PainterToken
{
	std::string str;
};


class PaintingRule;

class Painter
{
public:
	Painter() = default;


	std::string paint(const std::string& source);


	void add_rule(const PaintingRule& constraint) noexcept { rules_.push_back(constraint); }


private:
	std::vector<PaintingRule> rules_;
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


	bool match(std::string& str) const noexcept;


	std::string matcher_;

	ColorString color_;
};


SPECTER_NAMESPACE_END