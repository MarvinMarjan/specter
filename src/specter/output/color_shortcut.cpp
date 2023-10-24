#include <specter/output/color_shortcut.h>



SPECTER_NAMESPACE ColorShortcut::ColorShortcut(const ColorString& color)
	: color_(color)
{}



std::string SPECTER_NAMESPACE ColorShortcut::operator()(const std::string& source) const noexcept
{
	return color_.paint(source);
}