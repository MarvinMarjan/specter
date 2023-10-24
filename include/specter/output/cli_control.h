#pragma once

#include <specter/string.h>
#include <specter/output/escape.h>



SPECTER_NAMESPACE_BEGIN


enum EraseMode
{
	FromCursorToEnd,
	FromCursorToBegin,
	Entire
};



inline std::string cursor_home() noexcept {
	return HEX_ESC_CSI + 'H';
}


inline std::string cursor_to(const unsigned int row, const unsigned int col) noexcept {
	return HEX_ESC_CSI + str(row) + ';' + str(col) + 'H';
}


inline std::string cursor_up(const unsigned int up) noexcept {
	return HEX_ESC_CSI + str(up) + 'A';
}


inline std::string cursor_down(const unsigned int down) noexcept {
	return HEX_ESC_CSI + str(down) + 'B';
}


inline std::string cursor_right(const unsigned int right) noexcept {
	return HEX_ESC_CSI + str(right) + 'C';
}


inline std::string cursor_left(const unsigned int left) noexcept {
	return HEX_ESC_CSI + str(left) + 'D';
}


inline std::string cursor_down_begin(const unsigned int down) noexcept {
	return HEX_ESC_CSI + str(down) + 'E';
}


inline std::string cursor_up_end(const unsigned int up) noexcept {
	return HEX_ESC_CSI + str(up) + 'F';
}


inline std::string cursor_to_col(const unsigned int col) noexcept {
	return HEX_ESC_CSI + str(col) + 'G';
}



inline std::string save_cursor_pos() noexcept {
	return HEX_ESC + '7';
}


inline std::string load_cursor_pos() noexcept {
	return HEX_ESC + '8';
}



inline std::string erase_line(const EraseMode mode) noexcept {
	return HEX_ESC_CSI + str((int)mode) + 'K';
}


inline std::string erase_screen(const EraseMode mode) noexcept {
	return HEX_ESC_CSI + str((int)mode) + 'J';
}


SPECTER_NAMESPACE_END