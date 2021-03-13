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

//----- only uses operations: shifts, adding, and

/**
 * Highly Optimized bit counting
 * using a temporary variable c
 */
u8 Algorithms::CountBitsset::parallel32(u32 const v) noexcept{
  u32 c; // store the total here
  //Shifts
  static const u8 S[] = {1, 2, 4, 8, 16};
  //Masks
  static const u32 M[] = {0x55555555ul, 0x33333333ul,
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
  u64 c; // store the total here
  //Shifts
  static const u8 S[] = {1, 2, 4, 8, 16, 32};
  //Masks
  static const u64 M[] = {0x5555555555555555ull, 0x3333333333333333ull,
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
  u32 x = v;
  //2bit bucket
  x -=  ((x >> 1) & 0x55555555ul);
  //4bit bucket
  x  = (((x >> 2) & 0x33333333ul) + (x & 0x33333333ul));
  //8bit bucket
  x  = (((x >> 4) + x) & 0x0f0f0f0ful);

  x += (x >> 8);  //Sum two  8bit buckets
  x += (x >> 16); //Sum two 16bit buckets

  return u8(x & 0x0000003Ful);
}

/**
 * @brief parallel64_2
 * @param v
 * @return
 */
u8 Algorithms::CountBitsset::parallel64_2(u64 const v) noexcept{
  u64 x = v;
  //2bit bucket
  x -=  ((x >> 1) & 0x5555555555555555ull);
  //4bit bucket
  x  = (((x >> 2) & 0x3333333333333333ull) + (x & 0x3333333333333333ull));
  //8bit bucket
  x  = (((x >> 4) + x) & 0x0f0f0f0f0f0f0f0full);

  x += (x >> 8);  //Sum two  8bit buckets
  x += (x >> 16); //Sum two 16bit buckets
  x += (x >> 32); //Sum two 64bit buckets
  return u8(x & 0x000000000000007Ful);
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
  u32 c = v;
  //2bit buckets
  c-= ( (c >> 1) & 0x55555555ul);
  //4bit buckets
  c = ( (c >> 2) & 0x33333333ul) + (c & 0x33333333ul);
  //8bit buckets
  c = (((c >> 4) + c) & 0x0F0F0F0Ful);
  //sum all buckets
  c = (c * 0x01010101ul) >> 24;
  //
  return u8(c & 0x0000003Ful);
}

/**
 * @brief parallel64_3
 * @param v
 * @return
 */
u8 Algorithms::CountBitsset::parallel64_3(u64 const v) noexcept{
  u64 c = v;
  //2bit buckets
  c-= ((c >> 1) & 0x5555555555555555ull);
  //4bit buckets
  c = ((c >> 2) & 0x3333333333333333ull) + (c & 0x3333333333333333ull);
  //8bit buckets
  c = ((c + (c >> 4)) & 0x0F0F0F0F0F0F0F0Full);
  //sum all buckets
  c = (c * 0x0101010101010101ull) >> 56;
  //
  return u8(c & 0x000000000000007Full);
}

//-----

