#include <specter/output/color_object.h>



SPECTER_NAMESPACE ColorObject::ColorObject(const ModeIndex mode)
	: mode(mode) {}





SPECTER_NAMESPACE Color16Object::Color16Object(const ColorIndex color)
	: foreground(color) {}


SPECTER_NAMESPACE Color16Object::Color16Object(const ColorIndex color, const ModeIndex mode)
	: ColorObject(mode), foreground(color) {}


SPECTER_NAMESPACE Color16Object::Color16Object(const ColorIndex foreground, const ColorIndex background)
	: foreground(foreground), background(background) {}


SPECTER_NAMESPACE Color16Object::Color16Object(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode)
	: ColorObject(mode), foreground(foreground), background(background) {}





SPECTER_NAMESPACE Color256Object::Color256Object(const int color)
	: foreground(color) {}


SPECTER_NAMESPACE Color256Object::Color256Object(const int color, const ModeIndex mode)
	: ColorObject(mode), foreground(color) {}


SPECTER_NAMESPACE Color256Object::Color256Object(const int foreground, const int background)
	: foreground(foreground), background(background) {}


SPECTER_NAMESPACE Color256Object::Color256Object(const int foreground, const int background, const ModeIndex mode)
	: ColorObject(mode), foreground(foreground), background(background) {}





SPECTER_NAMESPACE ColorRGBObject::ColorRGBObject(const RGB& color)
	: foreground(color) {}


SPECTER_NAMESPACE ColorRGBObject::ColorRGBObject(const RGB& color, const ModeIndex mode)
	: ColorObject(mode), foreground(color) {}


SPECTER_NAMESPACE ColorRGBObject::ColorRGBObject(const RGB& foreground, const RGB& background)
	: foreground(foreground), background(background) {}


SPECTER_NAMESPACE ColorRGBObject::ColorRGBObject(const RGB& foreground, const RGB& background, const ModeIndex mode)
	: ColorObject(mode), foreground(foreground), background(background) {}







SPECTER_NAMESPACE ColorString::ColorString(const ColorObject& color)
	: str_color_(color.get()) {}


SPECTER_NAMESPACE ColorString::ColorString(const Color16Struct& color)
	: str_color_(clr(color)) {}


SPECTER_NAMESPACE ColorString::ColorString(const Color256Struct& color)
	: str_color_(clr(color)) {}


SPECTER_NAMESPACE ColorString::ColorString(const ColorRGBStruct &color)
	: str_color_(clr(color)) {}




SPECTER_NAMESPACE ColorString::ColorString(const ColorIndex color)
	: ColorString(Color16Struct(color)) {}


SPECTER_NAMESPACE ColorString::ColorString(const ColorIndex color, const ModeIndex mode)
	: ColorString(Color16Struct(color, mode)) {}


SPECTER_NAMESPACE ColorString::ColorString(const ColorIndex foreground, const ColorIndex background)
	: ColorString(Color16Struct(foreground, background)) {}


SPECTER_NAMESPACE ColorString::ColorString(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode)
	: ColorString(Color16Struct(foreground, background, mode)) {}




SPECTER_NAMESPACE ColorString::ColorString(const int color)
	: ColorString(Color256Struct(color)) {}


SPECTER_NAMESPACE ColorString::ColorString(const int color, const ModeIndex mode)
	: ColorString(Color256Struct(color, mode)) {}


SPECTER_NAMESPACE ColorString::ColorString(const int foreground, const int background)
	: ColorString(Color256Struct(foreground, background)) {}


SPECTER_NAMESPACE ColorString::ColorString(const int foreground, const int background, const ModeIndex mode)
	: ColorString(Color256Struct(foreground, background, mode)) {}




SPECTER_NAMESPACE ColorString::ColorString(const RGB& color)
	: ColorString(ColorRGBStruct(color)) {}


SPECTER_NAMESPACE ColorString::ColorString(const RGB& color, const ModeIndex mode)
	: ColorString(ColorRGBStruct(color, mode)) {}


SPECTER_NAMESPACE ColorString::ColorString(const RGB& foreground, const RGB& background)
	: ColorString(ColorRGBStruct(foreground, background)) {}


SPECTER_NAMESPACE ColorString::ColorString(const RGB& foreground, const RGB& background, const ModeIndex mode)
	: ColorString(ColorRGBStruct(foreground, background, mode)) {}