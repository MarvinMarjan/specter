#include <specter/output/color_shortcut.h>



SPECTER_NAMESPACE ColorShortcut::ColorShortcut(const ColorObject* const color)
	: color_(color)
{}



std::string SPECTER_NAMESPACE ColorShortcut::operator()(const std::string& source) const noexcept
{
	if (!color_)
		return source;

	return color_->paint(source);
}