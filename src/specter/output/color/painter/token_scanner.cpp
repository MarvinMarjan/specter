#include <specter/output/color/painter/token_scanner.h>

#include <specter/string.h>



SPECTER_NAMESPACE TokenScanner::TokenScanner(const std::string& source)
{
	source_ = source;

	begin_ = current_ = 0;
}


std::vector<SPECTER_NAMESPACE Token> SPECTER_NAMESPACE TokenScanner::scan() noexcept
{
	std::vector<Token> tokens;

	while (!at_end())
	{
		begin_ = current_;
		tokens.push_back(scan_token());
	}

	return tokens;
}



SPECTER_NAMESPACE Token SPECTER_NAMESPACE TokenScanner::scan_token() noexcept
{
	Token token;

	const char ch = advance();

	// only enters in this loop if "ch" is alpha num
	while (is_alphanum(ch) && is_alphanum(peek()))
		advance();

	// sub string
	token.source = source_.substr(begin_, current_ - begin_);

	token.begin = begin_;
	token.end = current_;

	return token;
}