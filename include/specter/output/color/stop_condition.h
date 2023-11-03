#pragma once

#include <specter/output/color/painter.h>



SPECTER_NAMESPACE_BEGIN


// says when a MatchRule must stop matching
class StopCondition
{
public:
	virtual bool stop() const noexcept = 0;
	virtual void process(Painter::MatchData& data) noexcept = 0;
	virtual void reload() noexcept = 0;
};



// matches an amount of tokens forward then stop
class RangeAmount : public StopCondition
{
public:
	RangeAmount(const unsigned int amount)
		: amount_init_(amount), amount_(amount) {}


	bool stop() const noexcept override { return amount_ == 0; }

	void process(Painter::MatchData& data) noexcept override { if (amount_ > 0) amount_--; }

	void reload() noexcept override { amount_ = amount_init_; }


private:
	unsigned int amount_;

	const unsigned int amount_init_;
};


// matches until a token
class UntilToken : public StopCondition
{
public:
	UntilToken(const std::string& token)
		: token_(token) {}


	bool stop() const noexcept override { return current_ == token_; }

	void process(Painter::MatchData& data) noexcept override { current_ = data.raw_token; }

	void reload() noexcept override { current_.clear(); }

	

private:
	std::string token_;
	std::string current_;
};


SPECTER_NAMESPACE_END