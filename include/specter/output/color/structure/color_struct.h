#pragma once

#include <specter/output/color/color.h>



SPECTER_NAMESPACE_BEGIN


template <typename T>
concept ValidColorType = Number<T> || std::same_as<T, RGB>;



// stores the foreground color, background color and a mode 
template <ValidColorType _ColorTy>
struct ColorStruct
{	
	ColorStruct() = default;


	ColorStruct(const _ColorTy foreground)
		: foreground(foreground) {}

	ColorStruct(const _ColorTy foreground, const ModeIndex mode)
		: foreground(foreground), mode(mode) {}

	ColorStruct(const _ColorTy foreground, const _ColorTy background)
		: foreground(foreground), background(background) {}

	ColorStruct(const _ColorTy foreground, const _ColorTy background, const ModeIndex mode)
		: foreground(foreground), background(background), mode(mode) {}


	_ColorTy foreground {-1};
	_ColorTy background {-1};

	ModeIndex mode = normal;
};



template <>
struct ColorStruct<ColorIndex>
{	
	ColorStruct() = default;


	ColorStruct(const ColorIndex foreground)
		: foreground(foreground) {}

	ColorStruct(const ColorIndex foreground, const ModeIndex mode)
		: foreground(foreground), mode(mode) {}

	ColorStruct(const ColorIndex foreground, const ColorIndex background)
		: foreground(foreground), background(background) {}

	ColorStruct(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode)
		: foreground(foreground), background(background), mode(mode) {}


	ColorIndex foreground = invalid;
	ColorIndex background = invalid;

	ModeIndex mode = normal;
};



using Color16Struct = ColorStruct<ColorIndex>;
using Color256Struct = ColorStruct<int>;
using ColorRGBStruct = ColorStruct<RGB>;




inline std::string clr(const std::string& source, const Color16Struct& color) noexcept
{ return clr(source, color.foreground, color.background, color.mode); }

inline std::string clr(const Color16Struct& color) noexcept
{ return clr(color.foreground, color.background, color.mode); }




inline std::string clr(const std::string& source, const Color256Struct& color) noexcept
{ return clr(source, color.foreground, color.background, color.mode); }

inline std::string clr(const Color256Struct& color) noexcept
{ return clr(color.foreground, color.background, color.mode); }




inline std::string clr(const std::string& source, const ColorRGBStruct& color) noexcept
{ return clr(source, color.foreground, color.background, color.mode); }

inline std::string clr(const ColorRGBStruct& color) noexcept
{ return clr(color.foreground, color.background, color.mode); }


SPECTER_NAMESPACE_END