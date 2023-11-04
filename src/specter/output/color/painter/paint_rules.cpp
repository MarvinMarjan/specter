#include <specter/output/color/painter/paint_rules.h>

#include <algorithm>

#include <specter/output/color/painter/match_data.h>



SPECTER_NAMESPACE Matcher::Matcher(const std::string& token)
	: matcher_({ token })
{}

SPECTER_NAMESPACE Matcher::Matcher(const std::initializer_list<std::string>& tokens)
	: matcher_(tokens)
{}


bool SPECTER_NAMESPACE Matcher::match(MatchData& data) const noexcept
{
	// tokens size is less than this matcher size. return
	if (data.tokens.size() - data.index_ < matcher_.size())
		return false;

	// tries to match with the token
	for (size_t i = 0; i < matcher_.size(); i++)
		if (matcher_[i] != data.tokens[data.index_ + i].source)
			return false;

	// token matched
	
	// paints the next tokens that are part of this matcher
	data.offset_ = matcher_.size() - 1;

	return true;
}




SPECTER_NAMESPACE MatcherRule::MatcherRule(const std::initializer_list<Matcher>& matchers, const ColorString& color, StopCondition* condition)
	: PaintRule(color, condition), matchers(matchers)
{}


bool SPECTER_NAMESPACE MatcherRule::token_match(MatchData& data) noexcept
{
	for (const Matcher& matcher : matchers)
		if (matcher.match(data))
			return true;

	return false;
}




SPECTER_NAMESPACE BetweenRule::BetweenRule(const Matcher& left, const Matcher& right, const ColorString& color, StopCondition* condition)
	: PaintRule(color, condition), left(left), right(right)
{
	opened_ = false;
}


bool SPECTER_NAMESPACE BetweenRule::token_match(MatchData& data) noexcept
{
	const bool eqleft = left.match(data);
	const bool eqright = right.match(data);

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




SPECTER_NAMESPACE CustomRule::CustomRule(MatchFunction matcher, const ColorString& color, StopCondition* condition)
	: PaintRule(color, condition), matcher(matcher)
{}


bool SPECTER_NAMESPACE CustomRule::token_match(MatchData& data) noexcept
{
	if (matcher)
		return matcher(data);

	return false;
}