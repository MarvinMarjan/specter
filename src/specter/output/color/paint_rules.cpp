#include <specter/output/color/paint_rules.h>

#include <algorithm>


SPECTER_NAMESPACE MatcherRule::MatcherRule(const std::initializer_list<std::string>& matchers, const ColorString& color)
	: PaintingRule(color), matchers(matchers)
{}



bool SPECTER_NAMESPACE MatcherRule::token_match(const std::string& token) const noexcept
{
	return (std::find(matchers.cbegin(), matchers.cend(), token) != matchers.cend());
}