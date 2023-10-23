#include <specter/output/color.h>

#include <sstream>



std::string SPECTER_NAMESPACE clr(const std::string& source, const std::initializer_list<int>& codes) noexcept
{
	std::stringstream stream;
	stream << HEX_ESC_CSI;

	for (auto it = codes.begin(); it != codes.end(); it++)
		stream << *it << (it + 1 == codes.end() ? "" : ";");

	stream << 'm' << source << RESET_ALL;
	return stream.str();
}
