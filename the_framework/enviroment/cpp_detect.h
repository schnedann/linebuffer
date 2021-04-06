/******************************************************************************/
/** Detect Language Standards / Features                                     **/
/** collected and / or implemented by                                        **/
/** see  https://sourceforge.net/p/predef/wiki/Standards/                    **/
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

#ifndef CPP_DETECT_H
#define CPP_DETECT_H

#ifndef __STDC_VERSION__
  #define __STDC_VERSION__ 199000L
#endif

#define dUSE_C94 	(__STDC_VERSION__==199409L)
#define dUSE_C99 	(__STDC_VERSION__==199901L)
#define dUSE_C11 	(__STDC_VERSION__==201112L)
#define dUSE_C18 	(__STDC_VERSION__==201710L)

#define dUSE_Cpp98 ((__cplusplus==199711L)||dUSE_Cpp11)
#define dUSE_Cpp11 ((__cplusplus==201103L)||dUSE_Cpp14)
#define dUSE_Cpp14 ((__cplusplus==201402L)||dUSE_Cpp17)
#define dUSE_Cpp17 ((__cplusplus==201703L)||dUSE_Cpp20)
#define dUSE_Cpp20 (__cplusplus==202002L)

namespace Enviroment {

constexpr bool const USE_C94 = dUSE_C94;
constexpr bool const USE_C99 = dUSE_C99;
constexpr bool const USE_C11 = dUSE_C11;
constexpr bool const USE_C18 = dUSE_C18;

constexpr bool const USE_Cpp98 = dUSE_Cpp98;
constexpr bool const USE_Cpp11 = dUSE_Cpp11;
constexpr bool const USE_Cpp14 = dUSE_Cpp14;
constexpr bool const USE_Cpp17 = dUSE_Cpp17;
constexpr bool const USE_Cpp20 = dUSE_Cpp20;

} //namespace


#endif // CPP_DETECT_H
