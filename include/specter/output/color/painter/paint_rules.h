#pragma once

#include <specter/output/color/painter/stop_condition.h>
#include <specter/output/color/painter/painter.h>

#include <functional>



SPECTER_NAMESPACE_BEGIN


class MatchData;


// represents a token matcher. can match two or more tokens as
// it was one. example: "->" (token '-' and '>')
class Matcher
{
public:
	Matcher(const std::string& token);
	Matcher(const std::initializer_list<std::string>& tokens);


	bool match(MatchData& data) const noexcept;


private:
	std::vector<std::string> matcher_;
};



// matches if the given value is listed in "matchers"
class MatcherRule : public PaintRule
{
public:
	MatcherRule(const std::initializer_list<Matcher>& matchers, const ColorString& color, StopCondition* condition = nullptr);


	std::vector<Matcher> matchers;

private:
	bool token_match(MatchData& data) noexcept override;

	void reload() noexcept override { matched_ = false; }


	bool matched_ = false;
};





// matches everything between "left" and "right"
class BetweenRule : public PaintRule
{
public:
	BetweenRule(const Matcher& left, const Matcher& right, const ColorString& color, StopCondition* condition = nullptr);


	Matcher left, right;

private:
	bool token_match(MatchData& data) noexcept override;

	void reload() noexcept override { opened_ = false; }


	bool opened_;
};





// matches using a custom lambda
class CustomRule : public PaintRule
{
public:
	using MatchFunction = std::function<bool (MatchData&)>;

	CustomRule(MatchFunction matcher, const ColorString& color, StopCondition* condition = nullptr);


	MatchFunction matcher = nullptr;

private:
	bool token_match(MatchData& data) noexcept override;
};


SPECTER_NAMESPACE_END