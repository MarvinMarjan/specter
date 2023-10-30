#pragma once

#include <specter/output/color/painter.h>



SPECTER_NAMESPACE_BEGIN


// matches if the given value is listed in "matchers"
class MatcherRule : public PaintingRule
{
public:
	MatcherRule(const std::initializer_list<std::string>& matchers, const ColorString& color);


	std::vector<std::string> matchers;

private:
	bool token_match(const std::string& token) override;
};




// matches everything between "left" and "right"
class BetweenRule : public PaintingRule
{
public:
	BetweenRule(const std::string& left, const std::string& right, const ColorString& color);


	std::string left, right;

private:
	bool token_match(const std::string& token) override;
	
	void reload() noexcept override { is_token_between_ = false; }


	bool is_token_between_;
};




// matches using a custom lambda
class CustomRule : public PaintingRule
{
public:
	using MatchFunction = bool (*)(const std::string&);

	CustomRule(MatchFunction matcher, const ColorString& color);


private:
	bool token_match(const std::string& token) override;


	MatchFunction matcher_ = nullptr;
};


SPECTER_NAMESPACE_END