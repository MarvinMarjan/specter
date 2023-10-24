#include <iostream>

#include <specter/output/color_shortcut.h>


using namespace sp;


int main()
{
	ColorShortcut quote(113);

	std::cout << *quote << "hello, world" << RESET_ALL << std::endl;
}