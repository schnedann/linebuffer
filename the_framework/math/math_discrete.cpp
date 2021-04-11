/******************************************************************************/
/** Algorithms for Integer Mathematics                                       **/
/** developed , collected and / or implemented by                            **/
/** Danny Schneider, 2017-2019                                               **/
/******************************************************************************/

/*
 * Copyright 2017-2019,Danny Schneider
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

#include "global_config.h"
#include "math_discrete.h"

#include <array>

using namespace Math::Discrete;
using namespace Math::Boolean;

//-----

/*
 * Next largest (Integer which is a) Power of 2
 */
u64 Math::Discrete::nlpo2(u64 const data, u8 const bits){
  u64 res = data;
  //Not Power of Two
  if(is_power_of_2<u64>(res)==0){
    //clog2(bits)
    for(u8 ii=1; ii<bits; ii<<=1){
      //Set all Lower Bits
      res |= (res >> ii);
    }
    res += 1;
  }
  return res;
}

//-----

//-----

/* Prototype Code...

s64 div_ceil(s64 numerator, s64 denominator){
  std::lldiv_t res = std::lldiv(numerator, denominator);
  return (res.rem)?(res.quot+1):(res.quot);
}

s64 div_to_zero(s64 n, s64 d){
 return n / d;
} //as per C++11 standard note 80

s64 div_up(s64 n, s64 d) {
  return (n / d) + (((n < 0) ^ (d > 0)) && (n % d));
} //i.e. +1 iff (not exact int && positive result)

s64 div_down(s64 n, s64 d) {
  return n / d - (((n > 0) ^ (d > 0)) && (n % d));
} //i.e. +1 iff (not exact int && negative result)

s64 div_to_nearest(s64 n, s64 d) {
  return (2*n - d + 2*(true&&((n<0)^(d>0)))*d) / (2*d);
} //i.e. +-0.5 as per pre-rounding result sign, then div_to-zero
//it however rounds numbers like +/- 3.5 towards 0 and not even.

*/

/**
 * Signed Division with rounding Mode Ceil()
 * eg. Gnu Compiler rounds to Zero normaly
 */
s16 Math::Discrete::sdivceil(s16 const a, s16 const b){
  s16 div = a / b;
  if (((a ^ b) >= 0) && (a % b != 0)){
      div++;
  }
  return div;
}

/**
 * Unsigned Division with rounding Mode Ceil()
 * eg. Gnu Compiler rounds to Zero normaly
 */
u16 Math::Discrete::udivceil(u16 const a, u16 const b){
  u16 div = a / b;
  if (a % b != 0){
    div++;
  }
  return div;
}


//--------------------------------------------------------------------------------

/**
 * Inverse square Root
 * see: http://en.wikipedia.org/wiki/Fast_inverse_square_root
 */
float Q_rsqrt(float const number ){
  auto const x2 = number * 0.5F;
  auto const tmp = 0x5F375A86f - (*(reinterpret_cast<u32 const *>(&number))>>1);
  auto y = *(reinterpret_cast<float const *>(&tmp));
  y  = y * ( 1.5F - ( x2 * y * y ) );   // 1st iteration
  y  = y * ( 1.5F - ( x2 * y * y ) );   // 2nd iteration, this can be removed
  return y;
}
double Q_rsqrt(double const number ){
  auto const x2 = number * 0.5;
  auto const tmp = 0x5FE6EB50C7B537A9 - (*(reinterpret_cast<u64 const *>(&number))>>1);
  auto y = *(reinterpret_cast<float const *>(&tmp));
  y  = y * ( 1.5 - ( x2 * y * y ) );   // 1st iteration
  y  = y * ( 1.5 - ( x2 * y * y ) );   // 2nd iteration, this can be removed
  return y;
}

//-----

//-----
