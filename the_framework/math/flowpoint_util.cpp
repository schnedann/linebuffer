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

#include <cmath>
#include <limits>
#include <cassert>

#include "bitmacros.h"
#include "flowpoint_util.h"
#include "iterators.h"

using namespace std;

//-----

/**
 * @brief Math::Flowpoint::AlmostEqual2sComplement
 * @note Ulp = unit in the last place or unit of least precision
 * @param A
 * @param B
 * @param maxUlps
 * @return
 */
bool Math::Flowpoint::AlmostEqual2sComplement(float A, float B, s32 maxUlps){
  bool res = false;
  constexpr auto const mask = Math::Boolean::MASK_MSB<s32>(Math::Boolean::GETBITSOFTYPE<s32>());
  // Make sure maxUlps is non-negative and small enough that the
  // default NAN won't compare as equal to anything.
  assert((maxUlps > 0) && (maxUlps < static_cast<s32>(Math::Boolean::GETFULLMASK<u32>(31))));

  s32 aInt = *(reinterpret_cast<Core::Container::iterator_t<s32>>(&A));
  // Make aInt lexicographically ordered as a twos-complement int
  if(aInt < 0){
    aInt = mask - aInt;
  }
  // Make bInt lexicographically ordered as a twos-complement int
  s32 bInt = *(reinterpret_cast<Core::Container::iterator_t<s32>>(&B));
  if(bInt < 0){
    bInt = mask - bInt;
  }
  s32 intDiff = Math::Boolean::INTABS<s32>(aInt - bInt);
  if(intDiff <= maxUlps){
    res = true;
  }
  return res;
}

bool Math::Flowpoint::AlmostEqual2sComplement(double A, double B, s64 maxUlps){
  bool res = false;
  constexpr auto const mask = Math::Boolean::MASK_MSB<s64>(Math::Boolean::GETBITSOFTYPE<s64>());
  // Make sure maxUlps is non-negative and small enough that the
  // default NAN won't compare as equal to anything.
  assert((maxUlps > 0) && (maxUlps < static_cast<s64>(Math::Boolean::GETFULLMASK<u64>(63))));

  s64 aInt = *(reinterpret_cast<Core::Container::iterator_t<s64>>(&A));
  // Make aInt lexicographically ordered as a twos-complement int
  if(aInt < 0){
    aInt = mask - aInt;
  }
  // Make bInt lexicographically ordered as a twos-complement int
  s64 bInt = *(reinterpret_cast<Core::Container::iterator_t<s64>>(&B));
  if(bInt < 0){
    bInt = mask - bInt;
  }
  s64 intDiff = Math::Boolean::INTABS<s64>(aInt - bInt);
  if(intDiff <= maxUlps){
    res = true;
  }
  return res;
}

//-----
