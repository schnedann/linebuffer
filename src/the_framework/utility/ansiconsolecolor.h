#ifndef ANSICONSOLECOLOR_H
#define ANSICONSOLECOLOR_H

#include "Stringhelper.h"

namespace Utility {

namespace AnsiColor {

static auto reset_all = Utility::Strings::make_string_from_literal("\033[0m");
//clears all colors and styles (to white on black)

static auto bold_on = Utility::Strings::make_string_from_literal("\033[1m");
//bold on

static auto italic_on = Utility::Strings::make_string_from_literal("\033[3m");
//italics on

static auto underline_on = Utility::Strings::make_string_from_literal("\033[4m");
//underline on

static auto inverse_on = Utility::Strings::make_string_from_literal("\033[7m");
//inverse on - reverses foreground & background colors

static auto strikethrough_on = Utility::Strings::make_string_from_literal("\033[9m");
//strikethrough on

static auto bold_off = Utility::Strings::make_string_from_literal("\033[22m");
//bold off

static auto italic_off = Utility::Strings::make_string_from_literal("\033[23m");
//italics off

static auto underline_off = Utility::Strings::make_string_from_literal("\033[24m");
//underline off

static auto inverse_off = Utility::Strings::make_string_from_literal("\033[27m");
//inverse off

static auto strikethrough_off = Utility::Strings::make_string_from_literal("\033[29m");
//strikethrough offf

static auto fgblack = Utility::Strings::make_string_from_literal("\033[30m");
//set foreground color to black

static auto fgred = Utility::Strings::make_string_from_literal("\033[31m");
//set foreground color to red

static auto fggreen = Utility::Strings::make_string_from_literal("\033[32m");
//set foreground color to green

static auto fgyellow = Utility::Strings::make_string_from_literal("\033[33m");
//set foreground color to yellow

static auto fgblue = Utility::Strings::make_string_from_literal("\033[34m");
//set foreground color to blue

static auto fgmagenta = Utility::Strings::make_string_from_literal("\033[35m");
//set foreground color to magenta (purple)

static auto fgcyan = Utility::Strings::make_string_from_literal("\033[36m");
//set foreground color to cyan

static auto fghighgrey = Utility::Strings::make_string_from_literal("\033[37m");
//set foreground color to white

static auto fgdefault = Utility::Strings::make_string_from_literal("\033[39m");
//set foreground color to default (white)

static auto fggrey = Utility::Strings::make_string_from_literal("\033[90m");
static auto fghighred = Utility::Strings::make_string_from_literal("\033[91m");
static auto fghighgreen = Utility::Strings::make_string_from_literal("\033[92m");
static auto fghighyellow = Utility::Strings::make_string_from_literal("\033[93m");
static auto fghighblue = Utility::Strings::make_string_from_literal("\033[94m");
static auto fgpink = Utility::Strings::make_string_from_literal("\033[95m");
static auto fghighcyan = Utility::Strings::make_string_from_literal("\033[96m");
static auto fgwhite = Utility::Strings::make_string_from_literal("\033[97m");

//--------------------------------------------------



static auto bgblack = Utility::Strings::make_string_from_literal("\033[40m");
//set background color to black

static auto bgred = Utility::Strings::make_string_from_literal("\033[41m");
//set background color to red

static auto bggreen = Utility::Strings::make_string_from_literal("\033[42m");
//set background color to green

static auto bgyellow = Utility::Strings::make_string_from_literal("\033[43m");
//set background color to yellow

static auto bgblue = Utility::Strings::make_string_from_literal("\033[44m");
//set background color to blue

static auto bgmagenta = Utility::Strings::make_string_from_literal("\033[45m");
//set background color to magenta (purple)

static auto bgcyan = Utility::Strings::make_string_from_literal("\033[46m");
//set background color to cyan

static auto bgwhite = Utility::Strings::make_string_from_literal("\033[47m");
//set background color to white

static auto bgdefault = Utility::Strings::make_string_from_literal("\033[49m");
//set background color to default (white)

} //namespace

} //namespace

#endif // ANSICONSOLECOLOR_H
