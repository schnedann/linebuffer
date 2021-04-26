/******************************************************************************/
/** Discrete Integer Mathematics                                             **/
/** collected and / or implemented by                                        **/
/** Danny Schneider, 2017-2020                                               **/
/**  http://graphics.stanford.edu/~seander/bithacks.html                     **/
/**  http://gurmeet.net/puzzles/fast-bit-counting-routines/                  **/
/**  http://aggregate.org/MAGIC/                                             **/
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

#ifndef MATH_DISCRETE_H
#define MATH_DISCRETE_H

#include "dtypes.h"
#include "compile_guards.h"
#include "bitmacros.h"

//----------------------------------------

namespace Math{

namespace Averaging{

//----------------------------------------
//----- Averaging
//----------------------------------------

/*
 * Overflow Save Calculation of Mean Value of two Numbers
 * C = B + ((A-B)/2), Where A > B
 * Code automaticliy choose which is A, which B...
 *
 * For Consecutive Calculations of Mean for 'Value' do:
 * init:        C=0; or C=dMEAN2(Min,Max);
 * consecutive: C=dMEAN2(Value,C);
 */
#define dMEAN2(_x,_y) (((_x)>(_y))?(_y+(((_x)-(_y))>>T(1))):(_x+(((_y)-(_x))>>T(1))))

/**
 * calculate the mean of two values
 */
template<typename T> constexpr T mean_of_two(T const _x, T const _y) noexcept{
  //Compile::Guards::IsInteger<T>();
  return dMEAN2(_x,_y);
}

//----------------------------------------
//----- Median of Three
//----------------------------------------

/*
  x>y>z --> y
  x>z>y --> z
  z>x>y --> x
  y>x>z --> x
  y>z>x --> z
  z>y>x --> y
*/
#define dMEDIAN3(_x,_y,_z) (((_x)>(_y))?(((_y)>(_z))?(_y):(((_x)>(_z))?(_z):(_x))):(((_x)>(_z))?(_x):(((_y)>(_z))?(_z):(_y))))

/**
 * calculate the median of three values
 */
template<typename T> constexpr T median_of_three(T const _x, T const _y, T const _z) noexcept{
  return  dMEDIAN3(_x,_y,_z);
}


} //namespace

//----------------------------------------

namespace Discrete{

//--------------------------------------------------

/**
 * test if a number is odd
 */
template<typename T> constexpr bool is_odd(T const _x){
  Compile::Guards::IsInteger<T>();
  return ((_x&1)>0);
}

/**
 * test if a number is even
 */
  template<typename T> constexpr bool is_even(T const _x){
  Compile::Guards::IsInteger<T>();
  return ((_x&1)==0);
}

//--------------------------------------------------

/**
 * @brief multiply_low_part - Multiplication only uses half of Type T
 *  e.g. if your CPU only supports N/2 bits, this calculates the lower bits
 *  normaly thrown away when executing a N/2 Type multiplication
 * @param  x
 * @param  y
 * @return
 */
template<typename T> constexpr T multiply_low_part(T const _x, T const _y) noexcept{
  Compile::Guards::IsInteger<T>();
  constexpr u8 const hbits = sizeof(T)<<2;
  T const a = _x>>hbits;
  T const b = _x&((u64(1)<<hbits)-1);
  T const c = _y>>hbits;
  T const d = _y&((u64(1)<<hbits)-1);
  return (((b*c)<<hbits)+((a*d)<<hbits)+(b*d));
}

/**
 * @brief multiply_high_part - Multiplication only uses half of Type T
 *  e.g. if your CPU only supports N/2 bits, the result equals the
 *  normal result when executing a N/2 Type multiplication
 * @param  x
 * @param  y
 * @return
 */
template<typename T> constexpr T multiply_high_part(T const _x, T const _y) noexcept{
  Compile::Guards::IsInteger<T>();
  constexpr u8 const hbits = sizeof(T)<<2;
  T const a = _x>>hbits;
  T const b = _x&((u64(1)<<hbits)-1);
  T const c = _y>>hbits;
  T const d = _y&((u64(1)<<hbits)-1);
  return ((((b*d)>>hbits)+(a*d)+(b*c))>>hbits)+(a*c);
}

//--------------------------------------------------



//--------------------------------------------------

/**
 * @brief countbitsset - Highly Optimized bit counting
 *     using a temporary variable c
 * @param  v
 * @return
 */
template<typename T> constexpr u8 countbitsset(T const v){
  Compile::Guards::IsUnsigned<T>();
  /* 64-bit recursive reduction using SWAR...
  but first step is mapping 2-bit values
  into sum of 2 1-bit values in sneaky way
  */
  T x = v;
  x -=  ((x >> 1) & T(0x5555555555555555ull));
  x  = (((x >> 2) & T(0x3333333333333333ull)) + (x & T(0x3333333333333333ull)));
  x  = (((x >> 4) + x) & T(0x0f0f0f0f0f0f0f0full));
  x +=   (x >> 8);
  x +=   (x >> 16);
  return u8(x & T(0x000000000000001Ful));
}

//--------------------------------------------------

/**
 * Integer leading Zeros Count
 */
template<typename T> constexpr u8 leadingzeros(T const _x){
  constexpr u8 const tbits = Math::Boolean::GETBITSOFTYPE<T>();
  T v = _x;
  v |= (v >> 1);
  v |= (v >> 2);
  v |= (v >> 4);
  if(tbits> 8) v |= (v >> 8);
  if(tbits>16) v |= (v >> 16);
  if(tbits>32) v |= (v >> 32);
  return(tbits - countbitsset<T>(v));
}

//--------------------------------------------------

/**
 * @brief is_power_of_2
 *
 * @param  v
 * @return
 */
template<typename T> constexpr bool is_power_of_2(T const v){
  Compile::Guards::IsUnsigned<T>();
  return ((v&(v-1))==0);
}

/**
 * @brief DiscreteMath::nextpow2
 * @param _x
 * @return
 */
template<typename T> T nextpow2(T const _x){
  Compile::Guards::IsUnsigned<T>();
  constexpr u8 const tbits = Math::Boolean::GETBITSOFTYPE<T>();
  T lx = _x;
  --lx;
  lx |= lx >> 1;
  lx |= lx >> 2;
  lx |= lx >> 4;
  if(tbits> 8) lx |= lx >> 8;
  if(tbits>16) lx |= lx >> 16;
  if(tbits>32) lx |= lx >> 32;
  ++lx;
  return lx;
}

//--------------------------------------------------

/**
 * @brief intpower
 *  Integer Power x^p
 * @param value
 * @param step
 * @return
 */
template<class T> constexpr T intpower(T const x, T const p){
  Compile::Guards::IsUnsigned<T>();
  T res = x;
  if(0 == p){
    res = 1;
  }else if(p>1){
    T tmp = intpower(x, static_cast<T>(p>>1));
    if(0==(p%2)){
   res = tmp * tmp;
    }else{
   res *= tmp * tmp;
    }
  }
  return res;
}

/**
 * @brief minimum
 *
 * @param  x
 * @param  y
 * @return
 */
template<typename T> constexpr bool minimum(T const x, T const y){
  Compile::Guards::IsUnsigned<T>();
  return x+(((y-x)>>(Math::Boolean::GETBITSOFTYPE<T>()-1))&(y-x));
}

/**
 * @brief maximum
 *
 * @param  x
 * @param  y
 * @return
 */
template<typename T> constexpr bool maximum(T const x, T const y){
  Compile::Guards::IsUnsigned<T>();
  return x-(((x-y)>>(Math::Boolean::GETBITSOFTYPE<T>()-1))&(x-y));
}

/**
 * @brief dec2gray
 *
 * @param  v
 * @return
 */
template<typename T> constexpr T dec2gray(T const v){
  Compile::Guards::IsUnsigned<T>();
  return v^(v>>1);
}

//----------------------------------------



//----------------------------------------

/**
 * @brief nearrounddiv - rounds towards nearest integer
 *        e.g.  5/7 = 1 and  3/9=0
 *        e.g. 20/9 = 2 and 13/5=3
 * @param  x
 * @param  y
 * @return normal up/down rounding of integer division (C Compiler normally rounds towards zero for positive numbers)
 */
template<typename T> constexpr T nearrounddiv(T const x, T const y){
  Compile::Guards::IsSigned<T>();
  return ((x+(y>>1))/y);
}

/**
 * @brief uiround
 *  Round to nearest unsigned int with steping step - expecting T as unsigned Integer Type
 * @param value
 * @param step
 * @return
 */
template<class T> constexpr auto uiround(T const value, T const step) -> T{
  Compile::Guards::IsUnsigned<T>();
  T res = value;
  T tmp = value%step;
  if(tmp>=(step>>1)){
    res += (step-tmp);
  }else{
    res -= tmp;
  }
  return res;
}

//-----

/**
 *
 */
template<class T> auto linear_interpol(T const x1, T const x2, T const y1, T const y2, T const xz) -> T{
  T res = y1;
  T intermeadiate_result1 = y2-y1;
  T intermeadiate_result2 = xz-x1;
  decltype (intermeadiate_result1 * intermeadiate_result1) intermeadiate_result3 = intermeadiate_result1 * intermeadiate_result1;
  decltype (intermeadiate_result1 * intermeadiate_result1) intermeadiate_result4 = x2-x1;
  T intermeadiate_result5 = static_cast<T>(intermeadiate_result3/intermeadiate_result4);
  res += intermeadiate_result5;
  return res;
}

//-----

/*
 * Next largest Integer witch is a Power of 2
 * Example: 3,4 --> 4
 */
u64 nlpo2(u64 const data, u8 const bits);

//-----

//-----

//-----
float  Q_rsqrt( float const  number );
double Q_rsqrt( double const number );
//-----

/**
 * @brief integerSqrt
 *        https://en.wikipedia.org/wiki/Integer_square_root
 * @param x
 * @return floor(sqrt(x)) for x = unsigned Integer
 */
template<typename T> T integerSqrt(T const x){
  Compile::Guards::IsUnsigned<T>();
  T res = x;

  if(x>1){
    u8  shift = 0;
    T nShifted = 0;
    //We check for nShifted being x,
    //since some implementations of
    //logical right shifting shift modulo the word size.
    do{
      shift += 2;
      nShifted = x >> shift;
    }while((nShifted>0) && (nShifted!=x));

    shift -= 2;

    //Find digits of result.
    res = 0;
    bool run = true;
    while(run){
      res <<= 1;
      T candidateResult = res + 1;
//TODO: Overflow safe math injection here
      if ((candidateResult*candidateResult) <= (x >> shift)){
        res = candidateResult;
      }
      if(shift>0) shift -= 2;
      else break;
    }
  }
  return res;
}

//-----

/**
 * Greatest Common Divider
 */
template<typename T> T gcd(T a, T b){
  Compile::Guards::IsUnsigned<T>();
  T res = 0;
  if(b == 0){
    res = a;
  }else{
    res = gcd<T>(b, (a%b));
  }
  return res;
}

/**
 * Least Common Multiple
 */
template<typename T> T lcm(T a, T b){
  Compile::Guards::IsUnsigned<T>();
  T res = 0;
  res  = a * b;
  res /= gcd<T>(a,b);
  return res;
}

//--------------------------------------------------

/**
 * index of highest Bit
 * 0x10000 --> Result is 17
 * For C-Style Counting: Result-1
 */
#if dHiBitIndex == 1
u8 hibitindex(u32 _v){
  unsigned char res = 1;
  if(_v > 0xFFFF){
    res += 16;
    maSHR(_v,16);
  }
  if(_v > 0xFF){
    res += 8;
     maSHR(_v,8);
  }
  if(_v > 0xF){
    res += 4;
     maSHR(_v,4);
  }
  if(_v > 0x3){
    res += 2;
     maSHR(_v,2);
  }
  if(_v > 0x1){
    res += 1;
  }
  return res;
}
#endif

#if dHiBitIndex == 2
u8 hibitindex(u32 _v){
  u8 res = 1;
  if (_v==0){return 0;}
  if(mAND(_v,0xFFFF0000u)>0){res+=16;}
  if(mAND(_v,0xFF00FF00u)>0){res+= 8;}
  if(mAND(_v,0xF0F0F0F0u)>0){res+= 4;}
  if(mAND(_v,0xccccccccu)>0){res+= 2;}
  if(mAND(_v,0xaaaaaaaau)>0){res+= 1;}
  return res;
}
#endif

#if dHiBitIndex == 3
u8 hibitindex(u32 _v){
  u8 res = 31;
  if (_v==0){return 0;}
  if (mAND(_v,0xFFFF0000u)==0){res-=16;}
  if (mAND(_v,0xFF00FF00u)==0){res-= 8;}
  if (mAND(_v,0xF0F0F0F0u)==0){res-= 4;}
  if (mAND(_v,0xCCCCCCCCu)==0){res-= 2;}
  if (mAND(_v,0xAAAAAAAAu)==0){res-= 1;}
  return res;
}
#endif

//--------------------------------------------------

/**
 * value of highest Bit
 */
#if dHiBitValue == 1
u32 hibitvalue(u32 n){
  n |= mSHR(n, 1);
  n |= mSHR(n, 2);
  n |= mSHR(n, 4);
  n |= mSHR(n, 8);
  n |= mSHR(n,16);
  return n - (n >> 1);
}
#endif

#if dHiBitValue == 2
u32 hibitvalue(u32 n){
  n |= mSHR(n, 1);
  n |= mSHR(n, 2);
  n |= mSHR(n, 4);
  n |= mSHR(n, 8);
  n |= mSHR(n,16);
  return(n & ~(n >> 1));
}
#endif

//--------------------------------------------------

template<typename T> T divide_by_shift(T const _a, T const _b, bool const round=false){
  bool is_signed = std::is_signed<T>::value;

  T res = 0;

  if(_b>0){ //divisor
    if(_a != _b){
      auto rest = _a;
      while(rest>_b){
        size_t shift = 0;
        while(1){
          auto tmp = Math::Boolean::ARITHSHL<T>(_b,shift);
          bool do_shift = rest > (_b+tmp);
          bool signflip = is_signed & Math::Boolean::MASKBITS<T>(Math::Boolean::XOR<T>(_b,tmp),Math::Boolean::MASK_MSB<T>());
          if(do_shift && !signflip){
            ++shift;
          }else{
            if((rest != tmp) && !signflip){
              shift = (shift>0)?(shift-1):(shift);
            }
            break;
          }
        }
        res  += Math::Boolean::GETMASKBIT<T>(shift);
        rest -= Math::Boolean::ARITHSHL<T>(_b,shift);
      }

      if(round && (Math::Boolean::ARITHSHL<T>(rest,1)>=_b)){
          ++res;
      }
    }else{
      res = 1;
    }
  }
  return res;
}

//--------------------------------------------------

/**
 * @brief ceildiv - Integer Division with Rouning up
 *
 * @param  x
 * @param  y
 * @return
 */
template<typename T> constexpr T ceildiv(T const x, T const y){
  Compile::Guards::IsInteger<T>();
  return ((y>0)?((x+y-1)/y):(0));
  //return ((y>0)?(1+((x-1)/y)):(0)); //Alternate Code
}

// so far Code does not working with signed numners...
template<typename T> constexpr T ceildiv_v2(T const _x, T const _y){
  Compile::Guards::IsInteger<T>();
  return ((_y)!=0)?(((_x)>0)?(((((_x)-1)/(_y))+1)):((_x)/(_y))):(0);
}

/**
 * Signed Division with rounding Mode Ceil()
 * eg. Gnu Compiler rounds to Zero normaly
 */
template<typename T> T sdivceil(T const a, T const b){
  Compile::Guards::IsInteger<T>();
  T div = 0;
  if(b > 0){
    div = a / b;
    if (((a ^ b) >= 0) && ((a % b) != 0)){
      div++;
    }
  }
  return div;
}

/**
 * Unsigned Division with rounding Mode Ceil()
 * eg. Gnu Compiler rounds to Zero normaly
 */
template<typename T> T udivceil(T const a, T const b){
  Compile::Guards::IsUnsigned<T>();
  T div = 0;
  if(b > 0){
    div = a / b;
    if ((a % b) != 0){
      div++;
    }
  }
  return div;
}

/**
 *
 */
template<typename T> T udivround(T const _a, T const _b){
  Compile::Guards::IsUnsigned<T>();
  T div = 0;
  if(_b > 0){
    div = _a / _b;
    auto rest = _a - (div * _b);
    if(Math::Boolean::ARITHSHL<T>(rest,1)>=_b){
      ++div;
    }
  }
  return div;
}

//--------------------------------------------------

} //namespace

} //namespace

#endif // MATH_DISCRETE_H
