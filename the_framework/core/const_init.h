/******************************************************************************/
/** Calculate Value at Complile-time                                         **/
/** e.g. for initialisation with a single mov Assembler Instruction          **/
/** implemented and / or collected by                                        **/
/** Danny Schneider, 2018                                                    **/
/******************************************************************************/

/*
 * Copyright 2018,Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided, the following conditions are met:
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
 *
 * 3. Usage for military, goverment purposes or from any other state authority
 * is forbidden
 */

#ifndef CONST_INIT_H
#define CONST_INIT_H

namespace meta {

namespace init {

template<typename T> constexpr T listadd(T v) noexcept{
  return v;
}

template<typename T, typename... Args> constexpr T listadd(T first, Args... args) noexcept{
  return first + listadd(args...);
}

//---

template<typename T> constexpr T listor(T v) noexcept{
  return v;
}

template<typename T, typename... Args> constexpr T listor(T first, Args... args) noexcept{
  return first | listor(args...);
}

} //namespace

} //namespace



#endif // CONST_INIT_H
