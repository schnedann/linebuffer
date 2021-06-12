#ifndef ALTERNATE_DIVIDE_H
#define ALTERNATE_DIVIDE_H

#include <array>
#include "dtypes.h"
#include "compile_guards.h"
#include "bitmacros.h"

namespace Math{

namespace Alternate{

/**
 * Divide by using Shifts (Multiply by 2), Addition, Substraction
 */
template<typename T> T divide_by_mply(T const dividend, T const divider){
  Compile::Guards::IsUnsigned<T>();
  T res = 0;
  T rest = dividend;

  while(rest >= divider){
    u8 shift = 0;
    T tmp;
    do{
      ++shift;
      tmp = Math::Boolean::Logic_Shift_L<T>(divider,shift);
    }while(tmp<rest);
    --shift;
    res += Math::Boolean::Logic_Shift_L<T>(T(1),shift);
    rest-=Math::Boolean::Logic_Shift_L<T>(divider,shift);
  }
  return res;
}

/**
 * Divide by only using Addition, Substraction and Greater or Equal Compare
 */
template<typename T> T  divide_by_substact(T const dividend, T const divider){
  Compile::Guards::IsUnsigned<T>();
  T res = 0;
  T rest = dividend;
  if(rest>=divider){
    do{
      rest-=divider;
      ++res;
    }while(rest>=divider);
  }
  return res;
}

/**
 * Divide by using Shifts (Multiply by 2), Addition, Substraction
 * Using a predefined shiftlist
 */
template<typename T, u8 N> T divide_by_shifts(T const dividend, std::array<u8,N> const& shiftlist){
  Compile::Guards::IsUnsigned<T>();
  T divider = 0;
  for(auto shift:shiftlist){
    divider |= Math::Boolean::Logic_Shift_L<T>(T(1),shift);
  }

  T res = 0;
  T rest = dividend;
  if(rest>=divider){
    bool stop = false;
    while(!stop){
      for(auto shift:shiftlist){
        rest -= Math::Boolean::Logic_Shift_L<T>(T(1),shift);
      }
      ++res;
      if(rest<divider){
        stop = true;
        break;
      }
    }
  }
  return res;
}

/**
 * https://en.wikipedia.org/w/index.php?title=Ancient_Egyptian_multiplication&oldid=843594424
 */
template<typename T> T multiply_Russian_peasant(T const multiplicant, T const multiplier){
  Compile::Guards::IsUnsigned<T>();
  T res = 0;
  T a = (multiplicant<multiplier)?(multiplicant):(multiplier);
  T b = (a==multiplicant)?(multiplier):(multiplicant);
  do{
    if((a&1)>0) res+=b;
    a>>=1;
    b<<=1;
  }while(a>0);
  return res;
}

} //namespace

} //namespace

#endif // ALTERNATE_DIVIDE_H
