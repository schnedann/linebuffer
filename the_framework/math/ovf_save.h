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

#include <iostream>
#include <iomanip>
#include <type_traits>

#include "dtypes.h"
#include "bitmacros.h"
#include "compile_guards.h"
#include "math_discrete.h"

//------------------------------------------------------------------------------

#if __GNUC__

  // http://www.fefe.de/intof.html
  // typeof is a GNU Extension

/**
 * Finding out whether we can assign a value to a variable without truncation
 */
template<typename Ts,typename Td> auto testassign(Td dest, Ts src)->bool{
  Ts __x=src;
  Td __y=__x;
  return ( (__x==__y) && ((__x<1)==(__y<1)) )?((void)((dest)=__y),false):(true);
}

/**
 * Overflow Save
 * Adding arbitrary integers
 */
template<typename Ta,typename Tb, typename Tc> auto add_of(Ta a, Tb b, Tc c)->Tc{
  Ta __a=a;
  Tb __b=b;
  (__b<1)?(((Math::Boolean::__MIN<Tc>()-__b)<=__a)?(testassign<Tc,decltype (a+b)>(c,a+b)):(true)):
          (((Math::Boolean::__MAX<Tc>()-__b)>=__a)?(testassign<Tc,decltype (a+b)>(c,a+b)):(true));
}

/**
 * Overflow Save
 * Subtracting arbitrary integers
 */
template<typename Ta,typename Tb, typename Tc> auto sub_of(Ta a, Tb b, Tc c)->Tc{
  Ta __a=a;
  Tb __b=b;
  (__b<1)?(((Math::Boolean::__MAX<Tc>()+__b)>=__a)?(testassign<Tc,decltype (a-b)>(c,a-b)):(true)):
          (((Math::Boolean::__MIN<Tc>()+__b)<=__a)?(testassign<Tc,decltype (a-b)>(c,a-b)):(true));
}

#endif

//------------------------------------------------------------------------------

/**
 * Overflow save comparison of Integers
 * a > b  =>  1
 * a = b  =>  0
 * b > a  => -1
 */
//Variant: ((_a)>(_b))-((_b)>(_a))
template<typename T> u8 comp_int(T _a, T _b){
  return ((((_a)>(_b))?(1):(0))-(((_b)>(_a))?(1):(0)));
}

//------------------------------------------------------------------------------

namespace Math{

namespace OverflowSafe {

//----- Satturated, Overflow Save Add + Sub

/**
 * @brief General Purpose (signed) Saturated Addition
 *
 */
template<typename T> auto satt_sadd(T a, T b)->T{
  Compile::Guards::IsSigned<T>();
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
 * General Purpose Saturated Subtraction
 */
template<typename T> auto satt_ssub(T a, T b)->T{
  return satt_sadd<T>(a, (T(-1) * b));
}

/**
 *
 */
template<typename T> auto satt_uadd(T a, T b)->T{
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
template<typename T> auto satt_usub(T a, T b)->T{
  T res;
  if(b <= a){
    res = a - b;
  }else{
    res = Math::Boolean::__MIN<T>();
  }
  return res;
}

//-----

s32 satt_sadd32(s32 a, s32 b);
s16 satt_ssub(s16 a, s16 b);
s32 satt_ssub32(s32 a, s32 b);
//-----
u16 satt_uadd(u16 a, u16 b);
u16 satt_usub(u16 a, u16 b);
//-----

//-----

class ovf_save{
private:
  bool overflow;
public:
  ovf_save();
  ~ovf_save()=default;

  template<typename T> auto ceillog2(T const&)->u8;
  template<typename T> auto floorlog2(T const&)->u8;

  template<typename T> auto add(T const&,T const&)->T;
  template<typename T> auto sub(T const&,T const&)->T;
  template<typename T> auto mul(T const&,T const&)->T;
  template<typename T> auto div(T const&,T const&)->T;

  bool get_of() const;

  template<typename T> static auto mean(T const&,T const&)->T;
};

/**
 * ceil(log2)
 */
template<typename T> auto ovf_save::ceillog2(T const& val)->u8{
  // Leading Nibble Bits
  u8 const lut1[] = {1,1,2,2,3,3,3,3,4,4,4,4,4,4,4,4};
  // exact exponent of 2 dectection table
  bool const lut2[] = {false,true,true ,false,
                       true ,false,false,false,
                       true ,false,false,false,
                       false,false,false,false};
  u8 res = 0;
  if(val>0){
    u8 cnt = (sizeof(T)<<1);
    u8 nibble = cnt-1; //second higest nibble
    bool is_exact = false;
    do{
      u8 ndata = (val>>(nibble<<2))&0x0Fu;
      // ensure zero only bits for exact exponent of 2
      if((res>0) && (ndata>0)) is_exact &= false;
      //For leading nibble --> first log2 estimation
      if((res==0) && (ndata>0)){
        is_exact |= lut2[ndata];
        res = lut1[ndata];
        res += nibble<<2;
      }
      if(nibble>0) --nibble;
      --cnt;
    }while(cnt>0);
    // exact exponent of 2 correction
    if(is_exact) --res;
  }
  return res;
}

/**
 * floor(log2)
 */
template<typename T> auto ovf_save::floorlog2(T const& val)->u8{
  // Leading Nibble Bits
  u8  const lut1[] = {0,0,1,1,2,2,2,2,3,3,3,3,3,3,3,3};
  u8 res = 0;
  if(val>0){
    u8 cnt = (sizeof(T)<<1);
    u8 nibble = cnt-1; //second higest nibble
    do{
      u8 ndata = (val>>(nibble<<2))&0x0Fu;
      if((res==0) && (ndata>0)){
        res = lut1[ndata];
        res += nibble<<2;
      }
      if(nibble>0) --nibble;
      --cnt;
    }while(cnt>0);
  }
  return res;
}

template<typename T> auto ovf_save::add(T const& _a, T const& _b)->T{
  T res = _a + _b;
  overflow = (_a > res)?(true):(false);
  if(0){
    std::cout << int(_a )<< ", ";
    std::cout << int(_b )<< ", ";
    std::cout << int(res)<< ", ";
    std::cout << overflow << "\n";
  }
  return res;
}

template<typename T> auto ovf_save::sub(T const& _a, T const& _b)->T{
  T res = _a - _b;
  overflow = (res > _a)?(true):(false);
  if(0){
    std::cout << int(_a )<< ", ";
    std::cout << int(_b )<< ", ";
    std::cout << int(res)<< ", ";
    std::cout << overflow << "\n";
  }
  return res;
}

template<typename T> auto ovf_save::mul(T const& _a, T const& _b)->T{
  T res = _a * _b;
  overflow = (((sizeof(T)<<3)-ceillog2(_a))<ceillog2(_b))?(true):(false);
  return res;
}

template<typename T> auto ovf_save::div(T const& _a, T const& _b)->T{
  T res = _a / _b;
  overflow = false; //(res > _a)?(true):(false);
  return res;
}

/**
 * Overflow save mean
 */
template<typename T> auto ovf_save::mean(T const& _a, T const& _b)->T{
  Compile::Guards::IsInteger<T>();
  T res;
  if(_a<_b) _a + ((_b-_a)>>1);
  else      _b + ((_a-_b)>>1);
  return res;
}

} //Namespace

} //Namespace

#endif // OVERFLOWSAVE_H
