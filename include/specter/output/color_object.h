#pragma once

#include <specter/output/color.h>



SPECTER_NAMESPACE_BEGIN


class ColorObject
{
public:
	ColorObject() = default;
	ColorObject(const ModeIndex mode);


	virtual std::string paint(const std::string& source) noexcept = 0;


	ModeIndex mode = normal;
};




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