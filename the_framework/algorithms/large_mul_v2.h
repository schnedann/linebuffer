#ifndef LARGE_MUL_V2_H
#define LARGE_MUL_V2_H

#include "dtypes.h"
#include "bitmacros.h"
#include "log2.h"

namespace Math {

namespace Large_Mul {

// example 8x8=16 Bit
// 8Bit x   3Bit BarrelShrifter   = 15 Bit
// 8Bit x   7Bit Multiplier       = 15 Bit
// 15Bit x 15Bit Adder with Carry = 16 Bit
template<typename T, typename RT> RT mply(T const& _a, T const& _b){
  RT res = _a;

  //Distribute Workload for Barrelshifter & Multiplier
  auto const byshift = Math::Log2::floor_log2<T>(_b);
  auto const bymul   = Math::Boolean::CLRBITS<T>(_b,Math::Boolean::get_msb<T>(_b));

//cout << "dbg-byshift: " << (int)byshift << endl;
//cout << "dbg-bymul  : " << (int)bymul << endl;

  res <<= byshift;   //Barrel Shifter
  res += _a * bymul; //Minimized Multiplier

  return res;
}

} //namespace

} //namespace

#endif // LARGE_MUL_V2_H
