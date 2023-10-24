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


SPECTER_NAMESPACE_END