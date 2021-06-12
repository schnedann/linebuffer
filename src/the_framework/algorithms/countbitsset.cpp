/******************************************************************************/
/** Algorithms to count bits set in an integer                               **/
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

/**
  Using Code from:
  https://graphics.stanford.edu/~seander/bithacks.html
  From this Page: the code snippets here are in the public domain

  University of Kenntucky
  http://aggregate.org/MAGIC/

  For some good expaination for the "Highly Optimized bit counting"
  see: http://en.wikipedia.org/w/index.php?title=Hamming_weight&oldid=484217681
*/

#include "countbitsset.h"

//----- Count Bits Set to 1

/**
 * Most Efficient Code for the
 * Hamming Weight:
 * Count the Number of Set Bits
 */
/*u8 hamming_weight16(u16 val){
  u16 res=val;
  res -= (res >> 2) & 0x5555u;
  res  = (res & 0x3333u) + ((res >> 2) & 0x3333u);
  res  = (res + (res >> 4)) & 0x0f0fu;
  res += res >> 8;
  return static_cast<u8>(res & 0x1fu);
}*/

/*u8 hamming_weight32(u32 val){
  u32 res=val;
  res -= (res >> 2) & 0x55555555u;
  res  = (res & 0x33333333u) + ((res >> 2) & 0x33333333u);
  res  = (res + (res >> 4)) & 0x0f0f0f0fu;
  res += res >> 24;
  return static_cast<u8>(res & 0x1fu);
}*/

//----- only uses operations: shifts, adding, and

/**
 * Highly Optimized bit counting
 * using a temporary variable c
 */
u8 Algorithms::CountBitsset::parallel32(u32 const v) noexcept{
  u32 c=0; // store the total here
  //Shifts
  static constexpr std::array<u8,5> const S = {1, 2, 4, 8, 16};
  //Masks
  static constexpr std::array<u32,5> const M = {0x55555555ul, 0x33333333ul,
                                                0x0F0F0F0Ful, 0x00FF00FFul,
                                                0x0000FFFFul};
  //2bit bucket
  c = v - ((v >> 1) & M[0]);
  //4bit bucket
  c = ((c >> S[1]) & M[1]) + (c & M[1]);
  //8bit bucket
  c = ((c >> S[2]) + c) & M[2];
  //16bit bucket
  c = ((c >> S[3]) + c) & M[3];
  //32bit bucket
  c = ((c >> S[4]) + c) & M[4];
  //
  return u8(c);
}

/**
 * Highly Optimized bit counting
 * using a temporary variable c
 */
u8 Algorithms::CountBitsset::parallel64(u64 const v) noexcept{
  u64 c=0; // store the total here
  //Shifts
  static constexpr std::array<u8,6> const S = {1, 2, 4, 8, 16, 32};
  //Masks
  static constexpr std::array<u64,6> const M = {0x5555555555555555ull, 0x3333333333333333ull,
                                                0x0F0F0F0F0F0F0F0Full, 0x00FF00FF00FF00FFull,
                                                0x0000FFFF0000FFFFull, 0x00000000FFFFFFFFull};
  //2bit bucket
  c = v - ((v >> S[0]) & M[0]);
  //4bit bucket
  c = ((c >> S[1]) & M[1]) + (c & M[1]);
  //8bit bucket
  c = ((c >> S[2]) + c) & M[2];
  //16bit bucket
  c = ((c >> S[3]) + c) & M[3];
  //32bit bucket
  c = ((c >> S[4]) + c) & M[4];
  //64bit bucket
  c = ((c >> S[5]) + c) & M[5];
  //
  return u8(c);
}

//----- only uses operations: shifts, adding, and

/**
 * Highly Optimized bit counting
 * using a temporary variable c
 */
/**
 * @brief parallel32_2
 * @param v
 * @return
 */
u8 Algorithms::CountBitsset::parallel32_2(u32 const v) noexcept{
  static constexpr u32 const mask_2bit   = 0x55555555ul;
  static constexpr u32 const mask_4bit   = 0x33333333ul;
  static constexpr u32 const mask_8bit   = 0x0F0F0F0Ful;
  static constexpr u64 const mask_result = 0x0000003Ful;
  u32 x = v;
  //2bit bucket
  x -=  ((x >> 1) & mask_2bit);
  //4bit bucket
  x  = (((x >> 2) & mask_4bit) + (x & mask_4bit));
  //8bit bucket
  x  = (((x >> 4) + x) & mask_8bit);

  x += (x >> 8);  //Sum two  8bit buckets
  x += (x >> 16); //Sum two 16bit buckets

  return u8(x & mask_result);
}

/**
 * @brief parallel64_2
 * @param v
 * @return
 */
u8 Algorithms::CountBitsset::parallel64_2(u64 const v) noexcept{
  static constexpr u64 const mask_2bit   = 0x5555555555555555ull;
  static constexpr u64 const mask_4bit   = 0x3333333333333333ull;
  static constexpr u64 const mask_8bit   = 0x0F0F0F0F0F0F0F0Full;
  static constexpr u64 const mask_result = 0x000000000000007Ful;
  u64 x = v;
  //2bit bucket
  x -=  ((x >> 1) & mask_2bit);
  //4bit bucket
  x  = (((x >> 2) & mask_4bit) + (x & mask_4bit));
  //8bit bucket
  x  = (((x >> 4) + x) & mask_8bit);

  x += (x >> 8);  //Sum two  8bit buckets
  x += (x >> 16); //Sum two 16bit buckets
  x += (x >> 32); //Sum two 64bit buckets
  return u8(x & mask_result);
}

//----- More optimized but needs HW Multiplier

/**
 * Highly Optimized bit counting
 * v = 0000000001100101
 * Count the ones in groups of 2 Bits  - v-= ((v >> 1) & 0x55555555);
 * |00|00|00|00|01|10|01|01 => Result: |00|00|00|00|01|01|01|01| => Decimal |0|0|0|0|1|1|1|1|
 * Count the ones in groups of 4 Bits  - v = (v & 0x33333333) + ((v >> 2) & 0x33333333);
 * |0000|0000|0101|0101|  => Result:   |0000|0000|0010|0010|     => Decimal |0|0|2|2|
 * Count the ones in groups of 8 Bits  - v = (v + (v >> 4)) & 0x0F0F0F0F;
 * |0000|0000|0010|0010|  => Result:   |00000000|00000100|       => Decimal |0|4|
 * Sum Groups up                       - v = (v * 0x01010101) >> 24;
 * |00000000|00000100|    => Result:   |000000000000100|         => Decimal |4|
 */
/**
 * @brief parallel32_3
 * @param v
 * @return
 */
u8 Algorithms::CountBitsset::parallel32_3(u32 const v) noexcept{
  static constexpr u32 const mask_2bit   = 0x55555555ul;
  static constexpr u32 const mask_4bit   = 0x33333333ul;
  static constexpr u32 const mask_8bit   = 0x0F0F0F0Ful;
  static constexpr u32 const mask_sum    = 0x01010101ul;
  static constexpr u32 const mask_result = 0x0000003Ful;
  u32 c = v;
  //2bit buckets
  c-= ( (c >> 1) & mask_2bit);
  //4bit buckets
  c = ( (c >> 2) & mask_4bit) + (c & mask_4bit);
  //8bit buckets
  c = (((c >> 4) + c) & mask_8bit);
  //sum all buckets
  c = (c * mask_sum) >> 24;
  //
  return u8(c & mask_result);
}

/**
 * @brief parallel64_3
 * @param v
 * @return
 */
u8 Algorithms::CountBitsset::parallel64_3(u64 const v) noexcept{
  static constexpr u64 const mask_2bit   = 0x5555555555555555ull;
  static constexpr u64 const mask_4bit   = 0x3333333333333333ull;
  static constexpr u64 const mask_8bit   = 0x0F0F0F0F0F0F0F0Full;
  static constexpr u64 const mask_sum    = 0x0101010101010101ull;
  static constexpr u64 const mask_result = 0x000000000000007Full;
  u64 c = v;
  //2bit buckets
  c-= ((c >> 1) & mask_2bit);
  //4bit buckets
  c = ((c >> 2) & mask_4bit) + (c & mask_4bit);
  //8bit buckets
  c = ((c + (c >> 4)) & mask_8bit);
  //sum all buckets
  c = (c * mask_sum) >> 56;
  //
  return u8(c & mask_result);
}

//-----

