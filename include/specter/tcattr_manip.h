#pragma once

#include <unistd.h>
#include <termios.h>



// get the terminal control attributes from "fd" (i.e: STDIN_FILENO)
inline termios get_tcattr(const int fd) noexcept
{
	struct termios tcattr;

	tcgetattr(fd, &tcattr);
	
	return tcattr;
}



// adds attributes to a terminal control flag
inline void add_tcflag_value(tcflag_t& flag, const int value) noexcept
{
	flag |= value;
}

// removes attributes from a terminal control flag
inline void rmv_tcflag_value(tcflag_t& flag, const int value) noexcept
{
	flag &= ~value;
}



// set attributes to "fd" file descriptor
inline void set_tcattr(const int fd, const termios& attr) noexcept
{
	tcsetattr(fd, TCSANOW, &attr);
}



// default stdin terminal control attributes
const termios default_stdin_tcattr = get_tcattr(STDIN_FILENO);


inline void set_default_stdin_tcattr() noexcept
{
	set_tcattr(STDIN_FILENO, default_stdin_tcattr);
}



// enables the continuous character input.
// the character pressed will be emited immediately,
// no need to press "enter"
inline void enable_continuous_input() noexcept
{
	termios tcattr = get_tcattr(STDIN_FILENO);			// get the current stdin attributes
	rmv_tcflag_value(tcattr.c_lflag, ICANON | ECHO);	// remove the necessary attributes
	set_tcattr(STDIN_FILENO, tcattr);					// set the modified attributes
}