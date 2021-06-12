/******************************************************************************/
/** Detect Posix compatibility                                               **/
/** see predefined macros @ Sourceforge                                      **/
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

#ifndef POSIX_DETECT_H
#define POSIX_DETECT_H

//Code by https://sourceforge.net/p/predef/wiki/Standards/

#if defined(unix) || defined(__unix__) || defined(__unix)
# define PREDEF_PLATFORM_UNIX
#endif
#if defined(PREDEF_PLATFORM_UNIX)
# include <unistd.h>
# if defined(_XOPEN_VERSION)
#  if (_XOPEN_VERSION >= 3)
#   define PREDEF_STANDARD_XOPEN_1989
#  endif
#  if (_XOPEN_VERSION >= 4)
#   define PREDEF_STANDARD_XOPEN_1992
#  endif
#  if (_XOPEN_VERSION >= 4) && defined(_XOPEN_UNIX)
#   define PREDEF_STANDARD_XOPEN_1995
#  endif
#  if (_XOPEN_VERSION >= 500)
#   define PREDEF_STANDARD_XOPEN_1998
#  endif
#  if (_XOPEN_VERSION >= 600)
#   define PREDEF_STANDARD_XOPEN_2003
#  endif
#  if (_XOPEN_VERSION >= 700)
#   define PREDEF_STANDARD_XOPEN_2008
#  endif
# endif
#endif

#endif // POSIX_DETECT_H
