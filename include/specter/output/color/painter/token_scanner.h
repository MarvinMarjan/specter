#pragma once

#include <string>
#include <vector>

#include <specter/macro.h>



SPECTER_NAMESPACE_BEGIN


struct Token
{
	std::string source;

	size_t begin;
	size_t end;
};



class TokenScanner
{
public:
	TokenScanner(const std::string& source);


	std::vector<Token> scan() noexcept;


private:
	Token scan_token() noexcept;


	bool at_end()		const	noexcept { return current_ >= source_.size(); }
	char peek()			const	noexcept { return source_[current_]; }
	char advance()				noexcept { return source_[current_++]; }


	std::string source_;

	size_t begin_;
	size_t current_;
};


SPECTER_NAMESPACE_END