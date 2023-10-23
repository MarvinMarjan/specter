#pragma once

#include <concepts>
#include <cstdint>

#include <specter/output/escape.h>



SPECTER_NAMESPACE_BEGIN


// basic color index. foreground and background
enum ColorIndex
{
	reset_color = 0, // reset color only


	// normal

	fg_black	= 30,	bg_black	= 40,
	fg_red 		= 31,	bg_red		= 41,
	fg_green	= 32,	bg_green	= 42,
	fg_yellow	= 33,	bg_yellow	= 43,
	fg_blue		= 34,	bg_blue		= 44,
	fg_magenta	= 35,	bg_magenta	= 45,
	fg_cyan		= 36,	bg_cyan		= 46,
	fg_white	= 37,	bg_white	= 47,
	fg_custom	= 38,	bg_custom	= 48,
	fg_default	= 39,	bg_default	= 49,


	// bright

	fg_bblack	= 90, 	bg_bblack	= 100,
	fg_bred 	= 91,	bg_bred		= 101,
	fg_bgreen	= 92, 	bg_bgreen	= 102,
	fg_byellow	= 93, 	bg_byellow	= 103,
	fg_bblue	= 94, 	bg_bblue	= 104,
	fg_bmagenta	= 95,	bg_bmagenta	= 105,
	fg_bcyan	= 96,	bg_bcyan	= 106,
	fg_bwhite	= 97,	bg_bwhite	= 107,
};


// color graphic mode
enum ModeIndex
{
	reset_all = 0, // ESC[0m - reset color and mode

	normal 		= 0, // ESC[0;...m - normal mode. not using this as first argument will also reset colors

	bold		= 1,	reset_bold		= 22,
	dim			= 2,	reset_dim		= 22,
	italic		= 3,	reset_italic	= 23,
	underline	= 4,	reset_underline	= 24,
	blinking	= 5,	reset_blinking	= 25,
	reverse		= 7,	reset_reverse	= 27,
	hidden		= 8,	reset_hidden	= 28,
	strike		= 9,	reset_strike	= 29
};


struct RGB;


// T is a number?
template <typename T>
concept Number = std::is_integral<T>::value;


template <typename T>
concept ValidColorType = Number<T> || std::same_as<T, RGB>;



// template <ValidColorType _ColorTy>
// struct ColorStruct
// {
// 	_ColorTy foreground;
// 	_ColorTy background;

// 	ModeIndex mode;
// };



struct RGB
{
	RGB() = default;
	RGB(const uint8_t r, const uint8_t g, const uint8_t b)
		: red(r), green(g), blue(b) {}

	RGB(const uint8_t all)
		: red(all), green(all), blue(all) {}


	uint8_t red		= 0;
	uint8_t green	= 0;
	uint8_t blue	= 0;
};




template <Number _NumTy>
inline std::string str(const _NumTy number) noexcept {
	return std::to_string(number);
}



const std::string RESET_ALL = HEX_ESC_CSI + "0m";


std::string clr(const std::string& source, const std::initializer_list<int>& codes) noexcept;
std::string clr(const std::initializer_list<int>& codes) noexcept;




inline std::string clr(const std::string& source, const ModeIndex mode) noexcept
{ return clr(source, {mode}); }

inline std::string clr(const ModeIndex mode) noexcept
{ return clr({mode}); }




inline std::string clr(const std::string& source, const ColorIndex color) noexcept
{ return clr(source, {color}); }

inline std::string clr(const ColorIndex color) noexcept
{ return clr({color}); }




inline std::string clr(const std::string& source, const ColorIndex color, const ModeIndex mode) noexcept
{ return clr(source, {mode, color}); }

inline std::string clr(const ColorIndex color, const ModeIndex mode) noexcept
{ return clr({mode, color}); }




inline std::string clr(const std::string& source, const ColorIndex foreground, const ColorIndex background) noexcept
{ return clr(source, {foreground, background}); }

inline std::string clr(const ColorIndex foreground, const ColorIndex background) noexcept
{ return clr({foreground, background}); }




inline std::string clr(const std::string& source, const ColorIndex foreground, const ColorIndex background, const ModeIndex mode) noexcept
{ return clr(source, {mode, foreground, background}); }

inline std::string clr(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode) noexcept
{ return clr({mode, foreground, background}); }




inline std::string clr(const std::string& source, const int id) noexcept
{ return clr(source, {fg_custom, 5, id}); }

inline std::string clr(const int id) noexcept
{ return clr({fg_custom, 5, id}); }




inline std::string clr(const std::string& source, const int id, const ModeIndex mode) noexcept
{ return clr(source, {mode, fg_custom, 5, id}); }

inline std::string clr(const int id, const ModeIndex mode) noexcept
{ return clr({mode, fg_custom, 5, id}); }




inline std::string clr(const std::string& source, const int foreground, const int background) noexcept
{ return clr(source, {fg_custom, 5, foreground, bg_custom, 5, background});
 }
inline std::string clr(const int foreground, const int background) noexcept
{ return clr({fg_custom, 5, foreground, bg_custom, 5, background}); }




inline std::string clr(const std::string& source, const int foreground, const int background, const ModeIndex mode) noexcept
{ return clr(source, {mode, fg_custom, 5, foreground, bg_custom, 5, background}); }

inline std::string clr(const int foreground, const int background, const ModeIndex mode) noexcept
{ return clr({mode, fg_custom, 5, foreground, bg_custom, 5, background}); }




inline std::string clr(const std::string& source, const RGB& color) noexcept
{ return clr(source, {fg_custom, 2, color.red, color.green, color.blue}); }

inline std::string clr(const RGB& color) noexcept
{ return clr({fg_custom, 2, color.red, color.green, color.blue}); }




inline std::string clr(const std::string& source, const RGB& color, const ModeIndex mode) noexcept
{ return clr(source, {mode, fg_custom, 2, color.red, color.green, color.blue}); }

inline std::string clr(const RGB& color, const ModeIndex mode) noexcept
{ return clr({mode, fg_custom, 2, color.red, color.green, color.blue}); }




inline std::string clr(const std::string& source, const RGB& foreground, const RGB& background) noexcept
{
	return clr(source, {fg_custom, 2,	foreground.red, foreground.green, foreground.blue,
						bg_custom, 2,	background.red, background.green, background.blue});
}




inline std::string clr(const std::string& source, const RGB& foreground, const RGB& background) noexcept
{
	return clr({fg_custom, 2,	foreground.red, foreground.green, foreground.blue,
				bg_custom, 2,	background.red, background.green, background.blue});
}




inline std::string clr(const std::string& source, const RGB& foreground, const RGB& background, const ModeIndex mode) noexcept
{
	return clr(source, {mode, 	fg_custom, 2,	foreground.red, foreground.green, foreground.blue,
								bg_custom, 2,	background.red, background.green, background.blue});
}



inline std::string clr(const std::string& source, const RGB& foreground, const RGB& background, const ModeIndex mode) noexcept
{
	return clr({mode, 	fg_custom, 2,	foreground.red, foreground.green, foreground.blue,
						bg_custom, 2,	background.red, background.green, background.blue});
}


SPECTER_NAMESPACE_END