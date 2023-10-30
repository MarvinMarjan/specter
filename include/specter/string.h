#pragma once

#include <concepts>
#include <string>

#include <specter/macro.h>



SPECTER_NAMESPACE_BEGIN


// T is a number?
template <typename T>
concept Number = std::is_integral<T>::value || std::convertible_to<T, int>;



template <Number _NumTy>
inline std::string str(const _NumTy number) noexcept {
	return std::to_string(number);
}


inline std::string chstr(const char ch) noexcept {
	return std::string(1, ch);
}




inline bool is_blank(const char ch) noexcept {
	return (ch == ' ' || ch == '\t' || ch == '\n' || ch == '\r');
}



inline bool is_alpha(const char ch) noexcept {
	return 	(ch >= 'A' && ch <= 'Z') || 
			(ch >= 'a' && ch <= 'z') ||
			ch == '_';
}

inline bool is_alpha(const std::string& str) noexcept
{
	for (const char ch  : str)
		if (!is_alpha(ch))
			return false;

	return true;
}



inline bool is_number(const char ch) noexcept {
	return (ch >= '0' && ch <= '9');
}

inline bool is_number(const std::string& str) noexcept
{
	for (const char ch : str)
		if (!is_number(ch))
			return false;

	return true;
}



inline bool is_alphanum(const char ch) noexcept {
	return is_alpha(ch) || is_number(ch);
}

inline bool is_alphanum(const std::string& str) noexcept
{
	return is_alpha(str) || is_number(str);
}


SPECTER_NAMESPACE_END