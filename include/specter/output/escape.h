#pragma once

#include <string>

#include <specter/macro.h>



SPECTER_NAMESPACE_BEGIN


const std::string OCT_ESC		= "\033";
const std::string OCT_ESC_CSI	= "\033[";

const std::string HEX_ESC		= "\x1b";
const std::string HEX_ESC_CSI	= "\x1b[";

const std::string UNI_ESC		= "\u001b";
const std::string UNI_ESC_CSI	= "\u001b[";


SPECTER_NAMESPACE_END