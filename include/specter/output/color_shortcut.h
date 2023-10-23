#pragma once

#include <specter/output/color_object.h>



SPECTER_NAMESPACE_BEGIN


class ColorShortcut
{
public:
	ColorShortcut() = default;
	ColorShortcut(const ColorObject* const color);


	std::string operator()(const std::string& src) const noexcept;


	const ColorObject* color() const noexcept { return color_; }

	void set_color(const ColorObject* const color) noexcept { color_ = color; }


private:
	const ColorObject* color_;
};


SPECTER_NAMESPACE_END