#include <specter/output/color/painter.h>

#include <sstream>

#include <specter/output/ostream.h>



std::string SPECTER_NAMESPACE Painter::paint(const std::string& source)
{
	// "source" is empty, just return it
	if (source.empty())
		return source;

	std::stringstream stream;
	std::string token;

	size_t begin = 0;
	size_t end = 0;

	// if code reachs here, it means "source" is not empty.
	// that way, we can ensure that at least one iteration will occur
	bool at_end = false;

	while (!at_end)
	{
		// set "begin" to "end"
		begin = end;

		// gets the current character and increments "end"
		const char ch = source[end++];

		// update "at_end" condition
		at_end = (end >= source.size());

		// blank characters like ' ', '\t', etc...
		if (is_blank(ch))
		{
			stream << ch;
			continue;
		}

		// find the last index of a word
		while (is_alphanum(source[end]))
			end++;

		// gets the current char/word substring
		token = source.substr(begin, end - begin);

		// match "token" until a rule matches it
		for (const PaintingRule& rule : rules_)
			if (rule.match(token))
				break;

		// add to "stream" the matched "token"
		stream << token;
	}

	return stream.str();
}




SPECTER_NAMESPACE PaintingRule::PaintingRule(const std::string& matcher, const ColorString& color)
{
	matcher_ = matcher;
	color_ = color;
}




bool SPECTER_NAMESPACE PaintingRule::match(std::string& str) const noexcept
{
	if (str != matcher_)
		return false;

	str.insert(0, color_.get());
	str += RESET_ALL;

	return true;
}