#pragma once

#include <specter/output/color/stop_condition.h>



SPECTER_NAMESPACE_BEGIN


// matches if the given value is listed in "matchers"
class MatcherRule : public PaintRule
{
public:
	MatcherRule(const std::initializer_list<std::string>& matchers, const ColorString& color, StopCondition* condition = nullptr);
	~MatcherRule();


	std::vector<std::string> matchers;

private:
	bool token_match(Painter::MatchData& data) noexcept override;

	void reload() noexcept override { matched_ = false; }


	StopCondition* cond_ = nullptr;
	bool matched_ = false;
};





// matches everything between "left" and "right"
class BetweenRule : public PaintRule
{
public:
	BetweenRule(const std::string& left, const std::string& right, const ColorString& color);


	std::string left, right;

private:
	bool token_match(Painter::MatchData& data) noexcept override;

	void reload() noexcept override { opened_ = false; }


	bool opened_;
};





// matches using a custom lambda
class CustomRule : public PaintRule
{
public:
	using MatchFunction = bool (*)(Painter::MatchData&) noexcept;

	CustomRule(MatchFunction matcher, const ColorString& color);


	MatchFunction matcher = nullptr;

private:
	bool token_match(Painter::MatchData& data) noexcept override;
};


SPECTER_NAMESPACE_END