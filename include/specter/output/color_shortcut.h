#pragma once

#include <specter/output/color_object.h>



SPECTER_NAMESPACE_BEGIN


class ColorShortcut
{
public:
	ColorShortcut() = default;
	ColorShortcut(const ColorString& color);


	std::string operator()(const std::string& src) const noexcept;


	ColorString color() const noexcept { return color_; }

	void set_color(const ColorString& color) noexcept { color_ = color; }


private:
	ColorString color_;
};


SPECTER_NAMESPACE_END