/******************************************************************************/
/** Overflow Save or aware functions needed for some DSP stuff               **/
/** collected and / or implemented by                                        **/
/** Danny Schneider, 2017-2020                                               **/
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

#ifndef OVERFLOWSAVE_H
#define OVERFLOWSAVE_H

//#include <iostream>
//#include <iomanip>
#include <type_traits>

#include "dtypes.h"
#include "bitmacros.h"
#include "log2.h"
#include "compile_guards.h"
//#include "math_discrete.h"

namespace Math{

namespace OverflowSafe {

//--------------------------------------------------

#if __GNUC__

  // http://www.fefe.de/intof.html
  // typeof is a GNU Extension

/**
 * Finding out whether we can assign a value stored as type Ts to a variable with type Td without truncation
 */
template<typename Ts,typename Td> bool testassign(Td dest, Ts const src){
  Compile::Guards::IsInteger<Ts>();
  Compile::Guards::IsInteger<Td>();
  Ts __x=src;
  Td __y=__x;
  return ( (__x==__y) && ((__x<1)==(__y<1)) )?((void)((dest)=__y),false):(true);
}

/**
 * Overflow Save
 * Adding arbitrary integers
 */
template<typename Ta,typename Tb, typename Tc> Tc add_of(Ta const a, Tb const b, Tc c){
  Compile::Guards::IsInteger<Ta>();
  Compile::Guards::IsInteger<Tb>();
  Compile::Guards::IsInteger<Tc>();
  Ta __a=a;
  Tb __b=b;
  bool res = (__b<1)?(((Math::Boolean::__MIN<Tc>()-__b)<=__a)?(testassign<Tc,decltype(a+b)>(c,a+b)):(true)):
             (((Math::Boolean::__MAX<Tc>()-__b)>=__a)?(testassign<Tc,decltype(a+b)>(c,a+b)):(true));
  return res;
}

/**
 * Overflow Save
 * Subtracting arbitrary integers
 */
template<typename Ta,typename Tb, typename Tc> Tc sub_of(Ta const a, Tb const b, Tc c){
  Compile::Guards::IsInteger<Ta>();
  Compile::Guards::IsInteger<Tb>();
  Compile::Guards::IsInteger<Tc>();
  Ta __a=a;
  Tb __b=b;
  bool res = (__b<1)?(((Math::Boolean::__MAX<Tc>()+__b)>=__a)?(testassign<Tc,decltype(a-b)>(c,a-b)):(true)):
             (((Math::Boolean::__MIN<Tc>()+__b)<=__a)?(testassign<Tc,decltype(a-b)>(c,a-b)):(true));
  return res;
}

#endif

//--------------------------------------------------

/**
 * Overflow save comparison of (signed) Integers
 * a > b  =>  1
 * a = b  =>  0
 * b > a  => -1
 */
//Variant: ((_a)>(_b))-((_b)>(_a))
template<typename T> s8 comp_int(T const _a, T const _b){
  Compile::Guards::IsInteger<T>();
  return static_cast<s8>((((_a)>(_b))?(1):(0))-(((_b)>(_a))?(1):(0)));
}

//--------------------------------------------------

/**
 * @brief Overflow aware addition
 */
template<typename T, typename RT=T> bool add(T const _a, T const _b, RT& _res){
  Compile::Guards::IsInteger<T>();
  static_assert (Math::Boolean::GETBITSOFTYPE<RT>()>=Math::Boolean::GETBITSOFTYPE<T>(),"Result Type must be GE Input Type");
  _res = static_cast<RT>(_a) + static_cast<RT>(_b);
  bool const overflow = (static_cast<RT>(_a) > _res)?(true):(false);
  return overflow;
}

/**
 * @brief Overflow aware substraction
 */
template<typename T, typename RT=T> bool sub(T const _a, T const _b, RT& _res){
  Compile::Guards::IsInteger<T>();
  static_assert (Math::Boolean::GETBITSOFTYPE<RT>()>=Math::Boolean::GETBITSOFTYPE<T>(),"Result Type must be GE Input Type");
  _res = static_cast<RT>(_a) - static_cast<RT>(_b);
  bool const overflow = (_res > static_cast<RT>(_a))?(true):(false);
  return overflow;
}

/**
 * @brief Overflow aware multiplication
 * @param _a   - input number A
 * @param _b   - input number B
 * @param _res - result A*B
 * @return true if result does not fit into type RT
 */
template<typename T, typename RT=T> bool mul(T const _a, T const _b, RT& _res){
  Compile::Guards::IsInteger<T>();
  static_assert (Math::Boolean::GETBITSOFTYPE<RT>()>=Math::Boolean::GETBITSOFTYPE<T>(),"Result Type must be GE Input Type");
  _res = _a * _b;
  //Check if complete result will fit into type T
  bool overflow = (Math::Boolean::GETBITSOFTYPE<RT>() - Math::Log2::ceil_log2<T>(_a)) < Math::Log2::ceil_log2<T>(_b);
  return overflow;
}

/**
 * @brief division
 */
template<typename T> void div(T const _a, T const _b, T& _res){
  Compile::Guards::IsInteger<T>();
  _res = _a / _b;
  return;
}

/**
 * Overflow save mean
 */
template<typename T> T meanof2(T const _a, T const _b){
  Compile::Guards::IsInteger<T>();
  //return ((_a<_b)?(_a):(_b))+(((_a<_b)?(_b-_a):(_a-_b))>>1);
  return (_a<_b)?(_a+((_b-_a)>>1)):(_b+((_a-_b)>>1));
}

//--------------------------------------------------

//----- Satturated, Overflow Save Add + Sub

/**
 * @brief General Purpose (signed) Saturated Addition
 *
 */
template<typename T> T satt_sadd(T const a, T const b){
  Compile::Guards::IsInteger<T>();
  using u_t = typename std::make_unsigned<T>::type;
  constexpr static T const maxs = Math::Boolean::__MAX_SIGNED<T>();
  constexpr static T const mins = Math::Boolean::__MIN_SIGNED<T>();
  u_t res = a;
  bool of=false;
  if(b > 0){
    if( (res > 0) && (res > (maxs - b)) ){
      res = maxs;
      of=true;
    }
  }else if(b < 0){
    if( (res < 0) && (res < (mins - b))){
      res = mins;
      of=true;
    }
  }
  if(!of) res += b;
  return res;
}

/**
 * General Purpose (signed) Saturated Subtraction
 */
template<typename T> T satt_ssub(T const a, T const b){
  Compile::Guards::IsInteger<T>();
  return satt_sadd<T>(a, (T(-1) * b));
}

/**
 *
 */
template<typename T> T satt_uadd(T const a, T const b){
  Compile::Guards::IsUnsigned<T>();
  T res;
  if(b <= (Math::Boolean::__MAX<T>()-a)){
    res = a + b;
  }else{
    res = Math::Boolean::__MAX<T>();
  }
  return res;
}

/**
 *
 */
template<typename T> T satt_usub(T const a, T const b){
  Compile::Guards::IsUnsigned<T>();
  T res;
  if(b <= a){
    res = a - b;
  }else{
    res = Math::Boolean::__MIN<T>();
  }
  return res;
}

//--------------------------------------------------

} //Namespace

} //Namespace

#endif // OVERFLOWSAVE_H
