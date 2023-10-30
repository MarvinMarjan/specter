#pragma once

#include <specter/output/color/painter.h>



SPECTER_NAMESPACE_BEGIN


class MatcherRule : public PaintingRule
{
public:
	MatcherRule(const std::initializer_list<std::string>& matchers, const ColorString& color);


	std::vector<std::string> matchers;

private:

	bool token_match(const std::string& token) const noexcept override;
};


SPECTER_NAMESPACE_END