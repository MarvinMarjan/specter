#include <specter/output/color/painter/paint_rules.h>

#include <algorithm>



SPECTER_NAMESPACE MatcherRule::MatcherRule(const std::initializer_list<std::string>& matchers, const ColorString& color, StopCondition* condition)
	: PaintRule(color), matchers(matchers), cond_(condition)
{}

SPECTER_NAMESPACE MatcherRule::~MatcherRule()
{
	if (cond_)
		delete cond_;
}


bool SPECTER_NAMESPACE MatcherRule::token_match(Painter::MatchData& data) noexcept
{
	const bool found = std::find(matchers.cbegin(), matchers.cend(), data.token) != matchers.cend();

	if (found)
	{
		matched_ = true;
		return true;
	}

	if (!cond_ || !matched_)
		return found;


	// continue force matching?
	if (!cond_->stop())
	{
		data.forcing_rule = this;
		cond_->process(data);
		return true;
	}
	
	// stop condition has reached

	data.forcing_rule = nullptr;
	matched_ = false;
	cond_->reload();

	return false;
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
	: PaintRule(color), matcher(matcher)
{}


bool SPECTER_NAMESPACE CustomRule::token_match(Painter::MatchData& data) noexcept
{
	if (matcher)
		return matcher(data);

	return false;
}