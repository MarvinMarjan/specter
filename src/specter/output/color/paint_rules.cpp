#include <specter/output/color/paint_rules.h>

#include <algorithm>


SPECTER_NAMESPACE MatcherRule::MatcherRule(const std::initializer_list<std::string>& matchers, const ColorString& color)
	: PaintingRule(color), matchers(matchers)
{}


bool SPECTER_NAMESPACE MatcherRule::token_match(const std::string& token)
{
	return (std::find(matchers.cbegin(), matchers.cend(), token) != matchers.cend());
}




SPECTER_NAMESPACE BetweenRule::BetweenRule(const std::string& left, const std::string& right, const ColorString& color)
	: PaintingRule(color), left(left), right(right)
{
	is_token_between_ = false;
}


bool SPECTER_NAMESPACE BetweenRule::token_match(const std::string& token)
{
	const bool eqleft = token == left;
	const bool eqright = token == right;

	if (!is_token_between_ && eqleft)
	{
		is_token_between_ = true;
		return true;
	}

	if (is_token_between_ && eqright)
	{
		is_token_between_ = false;
		return true;
	}

	return is_token_between_;
}





SPECTER_NAMESPACE CustomRule::CustomRule(MatchFunction matcher, const ColorString& color)
	: PaintingRule(color), matcher_(matcher)
{}


bool SPECTER_NAMESPACE CustomRule::token_match(const std::string& token)
{
	if (matcher_)
		return matcher_(token);

	return false;
}