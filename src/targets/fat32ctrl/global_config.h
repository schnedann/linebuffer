/******************************************************************************/
/** Configuration Flags                                                      **/
/** collected and / or implemented by                                        **/
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

#ifndef GLOBAL_CONFIG_H
#define GLOBAL_CONFIG_H

#define dUSE_DEBUG_CODE   0
#define dUSE_DEBUG_OUTPUT 1
#define dUSE_NPOS         1
#define dUSE_AVOIDMODULO  0

namespace Global{

namespace Config{

  constexpr static bool const cUSE_DEBUG_CODE  = dUSE_DEBUG_CODE;
  constexpr static bool const cUSE_NPOS        = dUSE_NPOS;
  constexpr static bool const cUSE_DBGOUT      = dUSE_DEBUG_OUTPUT;
  constexpr static bool const cUSE_AVOIDMODULO = dUSE_AVOIDMODULO;

} //namespace

} //namespace



#endif // GLOBAL_CONFIG_H
