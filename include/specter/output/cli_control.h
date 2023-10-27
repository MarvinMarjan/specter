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



// moves the cursor to the top-left position
inline std::string cursor_home() noexcept {
	return HEX_ESC_CSI + 'H';
}


// moves cursor to a specific row and column
inline std::string cursor_to(const unsigned int row, const unsigned int col) noexcept {
	return HEX_ESC_CSI + str(row) + ';' + str(col) + 'H';
}


// moves the cursor up
inline std::string cursor_up(const unsigned int up) noexcept {
	return HEX_ESC_CSI + str(up) + 'A';
}


// moves the cursor down
inline std::string cursor_down(const unsigned int down) noexcept {
	return HEX_ESC_CSI + str(down) + 'B';
}


// moves the cursor right
inline std::string cursor_right(const unsigned int right) noexcept {
	return HEX_ESC_CSI + str(right) + 'C';
}


// moves the cursor left
inline std::string cursor_left(const unsigned int left) noexcept {
	return HEX_ESC_CSI + str(left) + 'D';
}


// moves the cursor to the begin of the next line 
inline std::string cursor_down_begin(const unsigned int down) noexcept {
	return HEX_ESC_CSI + str(down) + 'E';
}


// moves the cursor to the end of the previous line
inline std::string cursor_up_end(const unsigned int up) noexcept {
	return HEX_ESC_CSI + str(up) + 'F';
}


// moves the cursor to a specific column
inline std::string cursor_to_col(const unsigned int col) noexcept {
	return HEX_ESC_CSI + str(col) + 'G';
}




// saves the cursor position in an internal buffer.
// use "load_cursor_pos" to move the cursor to the saved position
inline std::string save_cursor_pos() noexcept {
	return HEX_ESC + '7';
}


// see "save_cursor_pos"
inline std::string load_cursor_pos() noexcept {
	return HEX_ESC + '8';
}



// erases a line
inline std::string erase_line(const EraseMode mode) noexcept {
	return HEX_ESC_CSI + str((int)mode) + 'K';
}


// erases a screen (terminal)
inline std::string erase_screen(const EraseMode mode) noexcept {
	return HEX_ESC_CSI + str((int)mode) + 'J';
}



inline std::string hide_cursor() noexcept {
	return HEX_ESC_CSI + "?25l";
}

inline std::string show_cursor() noexcept {
	return HEX_ESC_CSI + "?25h";
}


SPECTER_NAMESPACE_END