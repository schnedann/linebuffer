/******************************************************************************/
/** Algorithms to count bits set in an integer                               **/
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

/**
  Using Code from:
  https://graphics.stanford.edu/~seander/bithacks.html
  From this Page: the code snippets here are in the public domain

  University of Kenntucky
  http://aggregate.org/MAGIC/

  For some good expaination for the "Highly Optimized bit counting"
  see: http://en.wikipedia.org/w/index.php?title=Hamming_weight&oldid=484217681
*/

#ifndef COUNTBITSSET_H
#define COUNTBITSSET_H

#include <array>

#include "dtypes.h"
#include "compile_guards.h"
#include "bitmacros.h"

namespace Algorithms {

namespace CountBitsset {

//-----

/**
 * Simple Lookup Table Algorithm
 * 4 Bit Lut
 * move window Mask to all nibbles of integer v
 * and Sum the results taken from the Lut
 */
template<typename T> u8 nibble_lut(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  static constexpr std::array<u8,16> const lut = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
  u8 c = 0;
  for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<T>();ii+=4){
    c += lut[((_v>>ii) & 0xFu)];
  }
  return c;
}

/**
 * Simple Lookup Table Algorithm
 * 4 Bit Lut
 * move window Mask to all Bytes of integer v
 * and analyse the two nibbles of the byte
 * in one cycle of the Loop => Loopcount reduced by 2
 * Sum the results taken from the Lut of each Nibble
 */
template<typename T> u8 nibble_lut2(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  static constexpr std::array<u8,16> const lut = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
  u8 c = 0;
  union tobytes_t{
    T value;
    u8 b[sizeof(T)];
  };
  tobytes_t x;
  x.value = _v;
  for(u8 ii=0; ii<sizeof(T);++ii){
    u8 const y = x.b[ii];
    c += lut[y & 0xFu];
    c += lut[y >> 4];
  }
  return c;
}

/**
 * Simple Lookup Table Algorithm
 * 4 Bit Lut
 * completely unrolled version
 * Access the bytes via a union => the compiler
 * decides if shifting or special byte access Opcodes
 * should be used
 * Sum the results taken from the Lut of each Nibble
 */
template<typename T> u8 nibble_lut_ur2(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  static constexpr std::array<u8,16> const lut = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
  constexpr static u8 const bytes = sizeof(T);
  u8 c = 0;
  union tobytes_t{
    T value;
    u8 b[bytes];
  };

  tobytes_t x;
  x.value = _v;

  u8 y = x.b[0];
  c += lut[y & 0xFu];
  c += lut[y >> 4];
  if(bytes>1){
    y = x.b[1];
    c += lut[y & 0xFu];
    c += lut[y >> 4];
  }
  if(bytes>2){
    y = x.b[2];
    c += lut[y & 0xFu];
    c += lut[y >> 4];

    y = x.b[3];
    c += lut[y & 0xFu];
    c += lut[y >> 4];
  }
  if(bytes>4){
    y = x.b[4];
    c += lut[y & 0xFu];
    c += lut[y >> 4];

    y = x.b[5];
    c += lut[y & 0xFu];
    c += lut[y >> 4];

    y = x.b[6];
    c += lut[y & 0xFu];
    c += lut[y >> 4];

    y = x.b[7];
    c += lut[y & 0xFu];
    c += lut[y >> 4];
  }
  return c;
}

/**
 * Simple Lookup Table Algorithm
 * 4 Bit Lut
 * completely unrolled version
 * Access the bytes via Nibble sized shifts
 * => Asuming Processor supports X-bit shifts in one Cycle
 * Sum the results taken from the Lut of each Nibble
 */
template<typename T> u8 nibble_lut_ur(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  static constexpr std::array<u8,16> const lut = {0,1,1,2,1,2,2,3,1,2,2,3,2,3,3,4};
  constexpr static u8 const bytes = sizeof(T);
  u8 c = 0;
  c += lut[( _v     & 0xFu)];
  c += lut[((_v>>4) & 0xFu)];
  if(bytes>1){
    c += lut[((_v>>8) & 0xFu)];
    c += lut[((_v>>12) & 0xFu)];
  }
  if(bytes>2){
    c += lut[((_v>>16) & 0xFu)];
    c += lut[((_v>>20) & 0xFu)];

    c += lut[((_v>>24) & 0xFu)];
    c += lut[((_v>>28) & 0xFu)];
  }
  if(bytes>4){
    c += lut[((_v>>32) & 0xFu)];
    c += lut[((_v>>36) & 0xFu)];

    c += lut[((_v>>40) & 0xFu)];
    c += lut[((_v>>44) & 0xFu)];

    c += lut[((_v>>48) & 0xFu)];
    c += lut[((_v>>52) & 0xFu)];

    c += lut[((_v>>56) & 0xFu)];
    c += lut[((_v>>60) & 0xFu)];
  }
  return c;
}

//----- only uses operations: shifts, adding, and

/**
 * Highly Optimized bit counting
 * using a temporary variable c
 */
u8 parallel32(u32 const v) noexcept;

/**
 * Highly Optimized bit counting
 * using a temporary variable c
 */
u8 parallel64(u64 const v) noexcept;

/**
 * @brief parallel - choose 32 or 64 bit implementation
 */
template<typename T> u8 parallel(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  constexpr static u8 const bytes = sizeof(T);
  u8 res;
  if(bytes>4){
    res = parallel64(_v);
  }else{
    res = parallel32(_v);
  }
  return res;
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
u8 parallel32_2(u32 const v) noexcept;

/**
 * @brief parallel64_2
 * @param v
 * @return
 */
u8 parallel64_2(u64 const v) noexcept;

/**
 * @brief parallel - choose 32 or 64 bit implementation
 */
template<typename T> u8 parallel_2(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  constexpr static u8 const bytes = sizeof(T);
  u8 res;
  if(bytes>4){
    res = parallel64_2(_v);
  }else{
    res = parallel32_2(_v);
  }
  return res;
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
u8 parallel32_3(u32 const v) noexcept;

/**
 * @brief parallel64_3
 * @param v
 * @return
 */
u8 parallel64_3(u64 const v) noexcept;

/**
 * @brief parallel - choose 32 or 64 bit implementation
 */
template<typename T> u8 parallel_3(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  constexpr static u8 const bytes = sizeof(T);
  u8 res;
  if(bytes>4){
    res = parallel64_3(_v);
  }else{
    res = parallel32_3(_v);
  }
  return res;
}

//-----

/**
 * @brief use Compiler implementation
 */
template<typename T> u8 intrinsic_popcnt(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
 return u8(__builtin_popcount(_v));
}

/**
 * @brief wegner_method == briankernighansway
 * @param v
 * @return
 */
template<typename T> u8 wegner_method(T const _v) noexcept{
  Compile::Guards::IsUnsigned<T>();
  u8 count=0;
  T x = _v;
  while(x>0){
    x &= x - 1;
    ++count;
  }
  return count;
}

} //namespace

} //namespace

#endif // COUNTBITSSET_H
