#pragma once

#include <string>

#include <specter/macro.h>



SPECTER_NAMESPACE_BEGIN


enum class CharCode
{
	null = 0,	// null

	SOH, 	// start of heading
	STX, 	// start of text
	ETX, 	// end of text
	EOT, 	// end of transmission
	ENQ, 	// enquiry
	ACK, 	// acknowledge
	BEL, 	// bell
	BS, 	// backspace
	TAB, 	// horizontal tab
	LF, 	// line feed
	VT, 	// vertical tab
	FF, 	// form feed
	CR, 	// carriage return
	SO, 	// shift out
	SI, 	// shift in
	DLE, 	// data link escape
	DC1, 	// device control 1
	DC2, 	// device control 2
	DC3, 	// device control 3
	DC4, 	// device control 4
	NAK, 	// negative acknowledge
	SYN, 	// synchronous idle
	ETB, 	// end of trans. block
	CAN, 	// cancel
	EM, 	// end of medium
	SUB, 	// substitute
	ESC, 	// escape
	FS, 	// file separator
	GS, 	// group separator
	RS, 	// record separator
	US, 	// unit separator

	char_space = 32,
	char_excl_mark,
	char_quote,
	char_hashtag,
	char_dollar_sign,
	char_percentage,
	char_ampersand,
	char_apostrophe,
	char_lparen,
	char_rparen,
	char_star,
	char_plus,
	char_comma,
	char_minus,
	char_dot,
	char_slash,
	
	char_0,
	char_1,
	char_2,
	char_3,
	char_4,
	char_5,
	char_6,
	char_7,
	char_8,
	char_9,

	char_colon,
	char_semicolon,
	char_less,
	char_equal,
	char_greater,
	char_inter_mark,
	char_at_sign,

	char_A = 65,
	char_B,
	char_C,
	char_D,
	char_E,
	char_F,
	char_G,
	char_H,
	char_I,
	char_J,
	char_K,
	char_L,
	char_M,
	char_N,
	char_O,
	char_P,
	char_Q,
	char_R,
	char_S,
	char_T,
	char_U,
	char_V,
	char_W,
	char_X,
	char_Y,
	char_Z,

	char_lsquare_paren,
	char_backslash,
	char_rsquare_paren,
	char_caret,
	char_underline,
	char_backtick,

	char_a = 97,
	char_b,
	char_c,
	char_d,
	char_e,
	char_f,
	char_g,
	char_h,
	char_i,
	char_j,
	char_k,
	char_l,
	char_m,
	char_n,
	char_o,
	char_p,
	char_q,
	char_r,
	char_s,
	char_t,
	char_u,
	char_v,
	char_w,
	char_x,
	char_y,
	char_z,

	char_lcurly_brace,
	char_pipe,
	char_rcurly_brace,
	char_tilde,

	DEL // delete
};



enum class EscCode
{
	up_arrow = 65,
	down_arrow,
	right_arrow,
	left_arrow,
};



class CursorPos
{
public:
	CursorPos() = default;


	constexpr void operator++(int) noexcept {
		if (index < limit)
			index++;
	}


	constexpr void operator--(int) noexcept {
		if (index)
			index--;
	}


	size_t index = 0;
	size_t limit = 0;
};


struct CursorStyle
{
	std::string color_start;
	std::string color_end;
	std::string at_end;
};


class Cursor
{
public:
	Cursor() = default;


	void draw(std::string& source) noexcept;


	CursorPos pos;
	CursorStyle style;
};


class Istream
{
public:
	Istream() = default;


	virtual std::string read() = 0;


protected:
	virtual bool process(const char ch) noexcept = 0;
	virtual void process_sub(const char ch) noexcept = 0;

	virtual std::string format() noexcept = 0;

	std::string m_data;
	Cursor m_cursor;
};



class StdIstream : public Istream
{
public:
	StdIstream();


	std::string read() override;

private:

	// processes "ch" and checks if it is a control key
	bool process(const char ch) noexcept override;

	// processes escape sequences like directional arrows
	void process_sub(const char ch) noexcept override;

	// return the current input data to be printed to the screen
	std::string format() noexcept override;
};


SPECTER_NAMESPACE_END