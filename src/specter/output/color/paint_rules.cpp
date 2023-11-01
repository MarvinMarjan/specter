#include <specter/output/color/paint_rules.h>

#include <algorithm>



SPECTER_NAMESPACE MatcherRule::MatcherRule(const std::initializer_list<std::string>& matchers, const ColorString& color)
	: PaintRule(color), matchers(matchers)
{}


bool SPECTER_NAMESPACE MatcherRule::token_match(Painter::MatchData& data) noexcept
{
	return (std::find(matchers.cbegin(), matchers.cend(), data.token) != matchers.cend());
}




SPECTER_NAMESPACE BetweenRule::BetweenRule(const std::string& left, const std::string& right, const ColorString& color)
	: PaintRule(color), left(left), right(right)
{
	opened_ = false;
}


bool SPECTER_NAMESPACE BetweenRule::token_match(Painter::MatchData& data) noexcept
{
	const bool eqleft = data.raw_token == left;
	const bool eqright = data.raw_token == right;

	// starts coloring until close
	if (eqleft && !opened_)
	{
		opened_ = true;
		data.forcing_rule = this;
		return true;
	}

	// end coloring
	if (eqright && opened_)
	{
		opened_ = false;
		data.forcing_rule = nullptr;
		return true;
	}

	return opened_;
}




SPECTER_NAMESPACE CustomRule::CustomRule(MatchFunction matcher, const ColorString& color)
	: PaintRule(color), matcher_(matcher)
{}


bool SPECTER_NAMESPACE CustomRule::token_match(Painter::MatchData& data) noexcept
{
	if (matcher_)
		return matcher_(data);

	return false;
}