#include <specter/output/color/color.h>

#include <sstream>



std::string SPECTER_NAMESPACE clr(const std::string& source, const std::initializer_list<int>& codes) noexcept
{
	return clr(codes) + source + RESET_ALL;
}



std::string SPECTER_NAMESPACE clr(const std::initializer_list<int>& codes) noexcept
{
	std::stringstream stream;
	stream << HEX_ESC_CSI;

	for (auto it = codes.begin(); it != codes.end(); it++)
	{
		if ((*it) < 0)
			continue;

		stream << *it << (it + 1 == codes.end() ? "" : ";");
	}

	stream << 'm';
	return stream.str();
}
