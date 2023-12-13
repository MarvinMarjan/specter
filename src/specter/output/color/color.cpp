#include <specter/output/color/color.h>

#include <sstream>

#include <specter/output/ostream.h>



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

		const bool is_at_end = it + 1 == codes.end();
		const bool is_next_invalid = is_at_end || *(it + 1) < 0;

		stream << *it << ((!is_next_invalid) ? ";" : "");
	}

	stream << 'm';
	return stream.str();
}
