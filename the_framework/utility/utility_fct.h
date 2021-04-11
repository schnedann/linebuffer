#ifndef UTILITY_FKT_H
#define UTILITY_FKT_H

#include "dtypes.h"
#include "compile_guards.h"
#include "bitmacros.h"
#include "math_discrete.h"
#include "log2.h"

namespace Utility {

namespace Numbers {

/**
 * Calculate needed hex-digits
 */
template<typename T> u8 gethexdigitscount(T num){
  Compile::Guards::IsUnsigned<T>();
  constexpr const u8 nibble_bits = 4;
  auto const u = Math::Log2::ceil_log2<T>(num);                   //Bits needed to represent states (result is wrong if num=onehot)
  auto const v = u8(Math::Discrete::ceildiv<u32>(u,nibble_bits)); //Caclulate nibbles needed
  u8 const w = (Math::Boolean::IS_ONEHOT<u8>(num))?(v+1):(v);     //Correct result if num is onehot
  return w;
}

/**
 * Calculate needed decimal places (e.g. for printing with constant width)
 * calculates log2(num)/log2(10) using fixpoint arithmetics
 */
template<typename T> u8 estimatedecimalplaces(T num){
  Compile::Guards::IsUnsigned<T>();
  //Scaling factor in Q27 format
  constexpr u32 sfactor = 40403563; //ceil(1./log2(10)./(1./2.^27))

  constexpr u8 const fixpoint_shift = 27; //5 significant bits, 27 fractional bits, as u64 will always fit in 20 places
  //Step 1 calculate log2(num)
  u32 bits  = Math::Log2::ceil_log2<T>(num);
      bits += (Math::Boolean::IS_ONEHOT<T>(num))?(1):(0);
  //Step 2 calculate log2(num)/log2(10)
  auto res = Math::Boolean::ARITHSHL<u32>(bits,fixpoint_shift);
       res = Math::Discrete::ceildiv<u32>(res,sfactor);
  //As we know the worst case result fits in 5 bits, we rescale the Q27 number back to Q0 and truncate to u8
  return static_cast<u8>(Math::Boolean::ARITHSHR<u32>(res,fixpoint_shift));
}

} //namespace

//--------------------------------------------------

} //namespace

#endif

