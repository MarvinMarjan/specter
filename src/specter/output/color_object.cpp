#include <specter/output/color_object.h>



SPECTER_NAMESPACE ColorObject::ColorObject(const ModeIndex mode)
	: mode(mode) {}





SPECTER_NAMESPACE Color16Object::Color16Object(const ColorIndex color)
	: foreground(color) {}


SPECTER_NAMESPACE Color16Object::Color16Object(const ColorIndex foreground, const ColorIndex background)
	: foreground(foreground), background(background) {}


SPECTER_NAMESPACE Color16Object::Color16Object(const ColorIndex foreground, const ColorIndex background, const ModeIndex mode)
	: ColorObject(mode), foreground(foreground), background(background) {}





SPECTER_NAMESPACE Color256Object::Color256Object(const int color)
	: foreground(color) {}


SPECTER_NAMESPACE Color256Object::Color256Object(const int foreground, const int background)
	: foreground(foreground), background(background) {}


SPECTER_NAMESPACE Color256Object::Color256Object(const int foreground, const int background, const ModeIndex mode)
	: ColorObject(mode), foreground(foreground), background(background) {}





SPECTER_NAMESPACE ColorRGBObject::ColorRGBObject(const RGB& color)
	: foreground(color) {}


SPECTER_NAMESPACE ColorRGBObject::ColorRGBObject(const RGB& foreground, const RGB& background)
	: foreground(foreground), background(background) {}


SPECTER_NAMESPACE ColorRGBObject::ColorRGBObject(const RGB& foreground, const RGB& background, const ModeIndex mode)
	: ColorObject(mode), foreground(foreground), background(background) {}