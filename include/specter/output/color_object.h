#pragma once

#include <specter/output/color.h>
#include <specter/output/color_struct.h>



SPECTER_NAMESPACE_BEGIN


// stores coloring information as objects
class ColorObject
{
public:
	ColorObject() = default;
	ColorObject(const ModeIndex mode);


	// paint "source" with this color
	virtual std::string paint(const std::string& source) const noexcept = 0;
	virtual std::string get() const noexcept = 0;


	ModeIndex mode = normal;
};




// color object for 16 colors (ColorIndex)
class Color16Object : public ColorObject
{
public:
	using ColorObject::ColorObject;

	Color16Object(const ColorIndex color);
	Color16Object(const ColorIndex color, const ModeIndex mode);
	Color16Object(const ColorIndex foreground, const ColorIndex background);
	Color16Object(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode);


	std::string paint(const std::string& source) const noexcept override { return clr(source, foreground, background, mode); }
	std::string get() const noexcept override { return clr(foreground, background, mode); }


	ColorIndex foreground = fg_default;
	ColorIndex background = bg_default;
};



// color object for 8-bit colors
class Color256Object : public ColorObject
{
public:
	using ColorObject::ColorObject;

	Color256Object(const int color);
	Color256Object(const int color, const ModeIndex mode);
	Color256Object(const int foreground, const int background);
	Color256Object(const int foreground, const int background, const ModeIndex mode);


	std::string paint(const std::string& source) const noexcept override { return clr(source, foreground, background, mode); }
	std::string get() const noexcept override { return clr(foreground, background, mode); }


	int foreground = 0;
	int background = 0;
};



// color object for RGB colors
class ColorRGBObject : public ColorObject
{
public:
	using ColorObject::ColorObject;

	ColorRGBObject(const RGB& color);
	ColorRGBObject(const RGB& color, const ModeIndex mode);
	ColorRGBObject(const RGB& foreground, const RGB& background);
	ColorRGBObject(const RGB& foreground, const RGB& background, const ModeIndex mode);


	std::string paint(const std::string& source) const noexcept override { return clr(source, foreground, background, mode); }
	std::string get() const noexcept override { return clr(foreground, background, mode); }


	RGB foreground;
	RGB background;
};




class ColorString
{
public:
	ColorString(const ColorObject& color);
	ColorString(const Color16Struct& color);
	ColorString(const Color256Struct& color);
	ColorString(const ColorRGBStruct& color);

	ColorString(const ColorIndex color);
	ColorString(const ColorIndex color, const ModeIndex mode);
	ColorString(const ColorIndex foreground, const ColorIndex background);
	ColorString(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode);

	ColorString(const int color);
	ColorString(const int color, const ModeIndex mode);
	ColorString(const int foreground, const int background);
	ColorString(const int foreground, const int background, const ModeIndex mode);

	ColorString(const RGB& color);
	ColorString(const RGB& color, const ModeIndex mode);
	ColorString(const RGB& foreground, const RGB& background);
	ColorString(const RGB& foreground, const RGB& background, const ModeIndex mode);


	std::string paint(const std::string& source) const noexcept { return str_color_ + source + RESET_ALL; }
	std::string get() const noexcept { return str_color_; }


private:
	std::string str_color_;
};


SPECTER_NAMESPACE_END