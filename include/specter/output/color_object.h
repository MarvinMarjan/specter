#pragma once

#include <specter/output/color.h>



SPECTER_NAMESPACE_BEGIN


// stores coloring information as objects
class ColorObject
{
public:
	ColorObject() = default;
	ColorObject(const ModeIndex mode);


	// paint "source" with this color
	virtual std::string paint(const std::string& source) noexcept = 0;


	ModeIndex mode = normal;
};




// color object for 16 colors (ColorIndex)
class Color16Object : public ColorObject
{
public:
	using ColorObject::ColorObject;

	Color16Object(const ColorIndex color);
	Color16Object(const ColorIndex foreground, const ColorIndex background);
	Color16Object(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode);


	std::string paint(const std::string& source) noexcept override { return clr(source, foreground, background, mode); }


	ColorIndex foreground = fg_default;
	ColorIndex background = bg_default;
};



// color object for 8-bit colors
class Color256Object : public ColorObject
{
public:
	using ColorObject::ColorObject;

	Color256Object(const int color);
	Color256Object(const int foreground, const int background);
	Color256Object(const int foreground, const int background, const ModeIndex mode);


	std::string paint(const std::string& source) noexcept override { return clr(source, foreground, background, mode); }


	int foreground = 0;
	int background = 0;
};



// color object for RGB colors
class ColorRGBObject : public ColorObject
{
public:
	using ColorObject::ColorObject;

	ColorRGBObject(const RGB& color);
	ColorRGBObject(const RGB& foreground, const RGB& background);
	ColorRGBObject(const RGB& foreground, const RGB& background, const ModeIndex mode);


	std::string paint(const std::string& source) noexcept override { return clr(source, foreground, background, mode); }


	RGB foreground;
	RGB background;
};


SPECTER_NAMESPACE_END