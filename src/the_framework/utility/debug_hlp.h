/******************************************************************************/
/** Debug Helper                                                             **/
/** developed , collected and / or implemented by                            **/
/** Danny Schneider, 2017-2021                                               **/
/******************************************************************************/

/*
 * Copyright 2017-2021,Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef DEBUG_HLP_H
#define DEBUG_HLP_H

#include <iostream>
#include <string>

#include "dtypes.h"
#include "Stringhelper.h"
#include "ansiconsolecolor.h"

#define ERROR_IMPL(_x) Utility::Strings::stradd<6>({Utility::AnsiColor::bold_on,    \
                                                    Utility::AnsiColor::fgred,      \
                                                    "Error: ",                      \
                                                    Utility::AnsiColor::bold_off,   \
                                                    (_x),                           \
                                                    Utility::AnsiColor::reset_all})

#define WARNING_IMPL(_x) Utility::Strings::stradd<7>({Utility::AnsiColor::bold_on,    \
                                                      Utility::AnsiColor::fgyellow,   \
                                                      "Warning: ",                    \
                                                      Utility::AnsiColor::bold_off,   \
                                                      Utility::AnsiColor::fgcyan,     \
                                                      (_x),                           \
                                                      Utility::AnsiColor::reset_all})

#define LINEINFO(_x) Utility::Strings::stradd<8>({Utility::AnsiColor::bold_on,    \
                                                  Utility::AnsiColor::fghighgrey, \
                                                  std::string(__FILE__),          \
                                                  "::",                           \
                                                  VAR2STR(__LINE__),          \
                                                  ": ",                           \
                                                  Utility::AnsiColor::reset_all,  \
                                                  (_x)})

#define ERRMSG(_x)  LINEINFO(ERROR_IMPL(_x))
#define WARNMSG(_x) LINEINFO(WARNING_IMPL(_x))

#define DBGOUT(_x) {if(Global::Config::cUSE_DBGOUT){std::cout << (_x) << "\n";}}
#define DBGPUT(_x) {if(Global::Config::cUSE_DBGOUT){std::cout << (_x);}}

#define ERROUT(_x) {if(Global::Config::cUSE_DBGOUT){std::cerr << ERRMSG(_x) << "\n";}}

#endif // DEBUG_HLP_H
