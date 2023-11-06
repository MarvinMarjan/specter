#pragma once

#include <iostream>

#include <specter/macro.h>



SPECTER_NAMESPACE_BEGIN


// print values to the terminal without newline at end
template <typename... _ValueTy>
inline void print(const _ValueTy&... values) noexcept {
	(std::cout << ... << values);
}


// print values to the terminal with newline at end
template <typename... _ValueTy>
inline void println(const _ValueTy&... values) noexcept {
	(std::cout << ... << values) << std::endl;
}




// print values to the terminal using wide-characters without newline at end
template <typename... _ValueTy>
inline void wprint(const _ValueTy&... values) noexcept {
	(std::wcout << ... << values);
}


// print values to the terminal using wide-characters with newline at end
template <typename... _ValueTy>
inline void wprintln(const _ValueTy&... values) noexcept {
	(std::wcout << ... << values) << std::endl;
}


SPECTER_NAMESPACE_END