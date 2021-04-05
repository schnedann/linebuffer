/******************************************************************************/
/** Simple Hash Functions / Hash-Function building Blocks                    **/
/** collected and / or implemented by                                        **/
/** Danny Schneider, 2017-2021                                               **/
/******************************************************************************/

/*
 * Copyright 2017-2020,Danny Schneider
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

#ifndef SIMPLE_HASH_FCT_H
#define SIMPLE_HASH_FCT_H

#include "dtypes.h"
#include "compile_guards.h"
#include "bitmacros.h"
#include "math_discrete.h"

namespace Math{

namespace Hashing{

//----------------------------------------
//----- HASHING
//----------------------------------------

template<typename T> auto modhash(T x, T y)noexcept -> T {
  return x%y;
}

template<typename T> auto binhash(T x, u8 bits)noexcept -> T {
  T const mask =  Math::Boolean::GETFULLMASK<T>(bits);
  return Math::Boolean::MASKBITS<T>(x,mask);
}

/*
 * Square a Number and take bits out of the middle,
 * these Bits are affected by all bit positions of
 * the original Number
 */
#define dMID_SQUARE(_x,_y) ((((_x)*(_x))>>(_y>>4))&dOFS_MAX(_y))

/**
 * @brief - Overflow Save Midsquare-hash
 */
template<typename T> auto midsquare(T x)noexcept -> T {
  u8 halfbits = Math::Boolean::GETBITSOFTYPE<T>()>>1;
  T high = Math::Discrete::multiply_high_part<T>(x,x);
  T low  = Math::Discrete::multiply_low_part<T>(x,x);
  low = Math::Boolean::ARITHSHR<T>(low,halfbits);
  low = Math::Boolean::SETVALUE<T>(low,Math::Boolean::GETVALUE<T>(high,0,halfbits),halfbits,halfbits);
  return low;
}

/**
 * @brief - Square a Number and take bits out of the middle,
 * these Bits are affected by all bit positions of the input value _x
 * utilize 64Bit temporary (max type for T is 32Bit!!!)
 * the original Number
 * @param _x - number to square
 * @param _y - covered bits
 */
template<typename T> auto midsquare_64(T const& _x, T const& _bits) noexcept ->T{
  Compile::Guards::IsUnsigned<T>();
  return static_cast<T>(((u64(_x)*u64(_x))>>(sizeof(T)<<1))&Math::Boolean::GETFULLMASK<u64>(_bits));
}

/**
 * @brief - combine 2 good hash values _x and _y to a better hash
 * Also we can produce different results with the iteration parameter iter,
 * like resolving hash collisions in a hash-table
 */
template<typename T> auto doublehash(T const& _x, T const& _y, T const& iter, T const& _M) noexcept ->T{
  Compile::Guards::IsUnsigned<T>();
  return (_x+T((u64(iter)*u64(iter))*_y)%_M);
}

} //namespace

} //namespace

#endif // SIMPLE_HASH_FCT_H
