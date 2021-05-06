/******************************************************************************/
/** Algorithms to calculate the Integer Log2                                 **/
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

#include "log2.h"

//--------------------------------------------------------------------------------

/**
 * Returns the floor form of binary logarithm for a 32 bit integer.
 * -1 is returned if n is 0.
 */
s32 Math::Log2::floorLog2_32(u32 n){
  u32 pos = 0;
  if (n >= 1<<16) { n >>= 16; pos += 16; }
  if (n >= 1<< 8) { n >>=  8; pos +=  8; }
  if (n >= 1<< 4) { n >>=  4; pos +=  4; }
  if (n >= 1<< 2) { n >>=  2; pos +=  2; }
  if (n >= 1<< 1) {           pos +=  1; }
  return (n==0)?(-1):(static_cast<s32>(pos));
}

/**
 * Returns the floor form of binary logarithm for a 32 bit integer.
 * -1 is returned if n is 0.
 */
s16 Math::Log2::floorLog2_16(u16 n){
  u32 pos = 0;
  if (n >= 1<< 8) { n >>=  8; pos +=  8; }
  if (n >= 1<< 4) { n >>=  4; pos +=  4; }
  if (n >= 1<< 2) { n >>=  2; pos +=  2; }
  if (n >= 1<< 1) {           pos +=  1; }
  return (n==0)?(-1):(static_cast<s16>(pos));
}

//-----

/**
 * @brief log2u32
 * @param _x
 * @return
 */
u8 Math::Log2::log2u32(u32 const _x){
  u32 lx = _x;

  std::array<u32,5> const b = {0x2, 0xC, 0xF0, 0xFF00, 0xFFFF0000};
  std::array<u32,5> const S = {1, 2, 4, 8, 16};

  u32 res = 0; // result of log2(_x) will go here
  for (ssize_t ii = 4; ii >= 0; --ii){ // unroll for speed...
    if ((lx & b.at(ii))>0){
      lx >>= S.at(ii);
      res |= S.at(ii);
    }
  }
  return u8(res);
}

//-----

/**
 * Equals floor(log2(_x))
 */
u8 Math::Log2::minilog2(u8 const _x){
  constexpr static u8 const c4 = 0xF0U; // 11110000
  constexpr static u8 const c3 = 0xCU;  // 00001100
  constexpr static u8 const c2 = 0x02U; // 00000010

  u8 dut = _x;
  u8 res = 0;
  //Bit in highest Nibble?
  if((dut&c4)>0){
    res += 4;  //must be >= 4
    dut >>= 4; //Throw away lower bits
  }
  //Bit in upper 2 Bits of nibble
  if((dut&c3)>0){
    res += 2;  //must be >= 2
    dut >>= 2; //Throw away lower bits
  }
  if((dut&c2)>0){
    res += 1;  //must be >= 1
  }
  return res;
}
