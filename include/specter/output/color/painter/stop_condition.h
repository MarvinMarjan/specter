#pragma once

#include <specter/output/color/painter/match_data.h>



SPECTER_NAMESPACE_BEGIN


// if attached to a PaintRule, when it matches, the rule will start
// paint the next tokens (even if they do not match) until the stopping condition is reached
class StopCondition
{
public:
	virtual bool stop()		const noexcept = 0;
	virtual bool proceed()	const noexcept { return !stop(); }

	virtual void process(MatchData& data) noexcept = 0;

	virtual void reload() noexcept = 0;
};



// matches an amount of tokens forward then stop
class RangeAmount : public StopCondition
{
public:
	RangeAmount(const size_t amount)
		: amount_init_(amount), amount_(amount) {}


	bool stop()		const noexcept override	{ return amount_ == 0; }

	void process(MatchData& data) noexcept override { if (amount_ > 0) amount_--; }

	void reload() noexcept override { amount_ = amount_init_; }


private:
	size_t amount_;

	const size_t amount_init_;
};


// matches until a token
class UntilToken : public StopCondition
{
public:
	UntilToken(const std::string& token)
		: token_(token) {}


	bool stop() const noexcept override { return current_ == token_; }

	void process(MatchData& data) noexcept override { current_ = data.token.source; }

	void reload() noexcept override { current_.clear(); }

	

private:
	std::string token_;
	std::string current_;
};


SPECTER_NAMESPACE_END