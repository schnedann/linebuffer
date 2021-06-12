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

#ifndef LOG2_H
#define LOG2_H

#include "dtypes.h"
#include "global_config.h"
#include "debug_hlp.h"
#include "compile_guards.h"
#include "bitmacros.h"
#include "bitreverse.h"
#include "countbitsset.h"

namespace Math {

namespace Log2 {

//--------------------------------------------------

/* Example Numbers - what are expected results?
 x =              0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
floor(log2(x)) -Inf  0  1  1  2  2  2  2  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
 ceil(log2(x)) -Inf  0  1  2  2  3  3  3  3  4  4  4  4  4  4  4  4  5  5  5  5  5  5  5  5  5
*/

/**
 * @brief log2
 *
 * @param  x
 * @return
 */
template<typename T> constexpr T log2(T const _x){
  Compile::Guards::IsUnsigned<T>();

  //get number of bits divided by 2 of type T
  constexpr u8 const halfbits = sizeof(T)<<2;
  T res = 0;

  if(_x>0){
    //Mask with all bits set in the upper half and zeros in the lower
    T mask = Math::Boolean::Logic_Shift_L<T>(Math::Boolean::GETFULLMASK<T>(halfbits),halfbits);
    //init shift by halfbits
    u8 shift = halfbits;

    while(shift>1){
      if(_x&mask){
        res += shift;
      }
      shift >>= 1;
      mask ^= (mask >> shift);
    };

    if(_x&mask){
      res += shift;
    }
    mask ^= (mask >> 1);
    if(_x&mask){
      res += shift;
    }
   //mask ^= (mask >> 1);
    --res;
  }
  return res;
}

//--------------------------------------------------

/* Example Numbers - what are expected results?
 x =              0  1  2  3  4  5  6  7  8  9 10 11 12 13 14 15 16 17 18 19 20 21 22 23 24 25
floor(log2(x)) -Inf  0  1  1  2  2  2  2  3  3  3  3  3  3  3  3  4  4  4  4  4  4  4  4  4  4
 ceil(log2(x)) -Inf  0  1  2  2  3  3  3  3  4  4  4  4  4  4  4  4  5  5  5  5  5  5  5  5  5
*/

/**
 * @brief ceil_log2 - Integer ceil(log2(_x))
 * @note Implementation is a binary search inside the Integer _x
 * @return the result can be interpreted as number of bits needed to represent _x states
 */
#if (dDEBUG_CODE>0)
template<typename T> u8 dbg_ceil_log2(T _x){
  Compile::Guards::IsUnsigned<T>();
  DBGOUT(_x)
  u8 idx = 0;
  if(_x>1){
    u8 mid = sizeof(T)<<2; //Bits of Type
    idx = mid;
    while(true){
      DBGOUT(u16(idx))
      T const ref = T(1)<<idx;
      DBGOUT(ref)
      u8 const nmid = mid>>1;
      DBGOUT(u16(nmid))

      if((ref==_x)){
        DBGOUT("EQ")
        break;
      }else if(_x < ref){
        DBGOUT("ST")
        if(nmid>0) idx -= nmid;
      }else{
        DBGOUT("GT")
        idx += (nmid>0)?(nmid):(1);
      }
      if(0==mid){
        DBGOUT("TERM")
        break;
      }

      mid = nmid;
      DBGOUT(u16(mid))
    }
  }
  return idx;
}
#endif
template<typename T> u8 ceil_log2(T _x){
  Compile::Guards::IsUnsigned<T>();
  u8 idx = 0;
  if(_x>1){
    u8 mid = sizeof(T)<<2; //Bits of Type
    idx = mid;
    while(true){
      T const ref = T(1)<<idx;
      u8 const nmid = mid>>1;
      if((ref==_x)){
        break;
      }else if(_x < ref){
        if(nmid>0) idx -= nmid;
      }else{
        idx += (nmid>0)?(nmid):(1);
      }
      if(0==mid){
        break;
      }
      mid = nmid;
    }
  }
  return idx;
}

/**
 * @brief floor_log2 - Integer floor(log2(_x))
 * @note Implementation is a binary search inside the Integer _x
 */
#if (dDEBUG_CODE>0)
template<typename T> u8 dbg_floor_log2(T _x){
  Compile::Guards::IsUnsigned<T>();
  DBGOUT(_x)
  u8 idx = 0;
  if(_x>1){
    u8 mid = sizeof(T)<<2; //Bits of Type
    idx = mid;
    while(true){
      DBGOUT(u16(idx))
      T const ref = T(1)<<idx;
      DBGOUT(ref)
      u8 const nmid = mid>>1;
      DBGOUT(u16(nmid))

      if((ref==_x)){
        DBGOUT("EQ")
        break;
      }else if(_x < ref){
        DBGOUT("ST")
        idx -= (nmid>0)?(nmid):(1);
      }else{
        DBGOUT("GT")
        if(nmid>0) idx += nmid;
      }
      if(0==mid){
        DBGOUT("TERM")
        break;
      }

      mid = nmid;
      DBGOUT(u16(mid))
    }
  }
  return idx;
}
#endif
template<typename T> u8 floor_log2(T _x){
  Compile::Guards::IsUnsigned<T>();
  u8 idx = 0;
  if(_x>1){
    u8 mid = sizeof(T)<<2; //Bits of Type
    idx = mid;
    while(true){
      T const ref = T(1)<<idx;
      u8 const nmid = mid>>1;
      if((ref==_x)){
        break;
      }else if(_x < ref){
        idx -= (nmid>0)?(nmid):(1);
      }else{
        if(nmid>0) idx += nmid;
      }
      if(0==mid){
        break;
      }
      mid = nmid;
    }
  }
  return idx;
}

//-----

/**
 * @brief is_power_of_2
 */
#if (dDEBUG_CODE>0)
template<typename T> bool dbg_is_power_of_2(T _x){
  Compile::Guards::IsUnsigned<T>();
  DBGOUT(_x)
  bool res = (1==_x)?(true):(false);
  u8 idx = 0;
  if(_x>1){
    u8 mid = sizeof(T)<<2; //Bits of Type
    idx = mid;
    while(true){
      DBGOUT(u16(idx))
      T const ref = T(1)<<idx;
      DBGOUT(ref)
      u8 const nmid = mid>>1;
      DBGOUT(u16(nmid))

      if((ref==_x)){
        DBGOUT("EQ")
        res = true;
        break;
      }else if(_x < ref){
        DBGOUT("ST")
        if(nmid>0) idx -= nmid;
      }else{
        DBGOUT("GT")
        idx += (nmid>0)?(nmid):(1);
      }
      if(0==mid){
        DBGOUT("TERM")
        break;
      }
      mid = nmid;
      DBGOUT(u16(mid))
    }
  }
  return res;
}
#endif

//-----

template<typename T> bool is_power_of_2(T _x){
  Compile::Guards::IsUnsigned<T>();
  bool res = (1==_x)?(true):(false);
  u8 idx = 0;
  if(_x>1){
    u8 mid = sizeof(T)<<2; //Bits of Type
    idx = mid;
    while(true){
      T const ref = T(1)<<idx;
      u8 const nmid = mid>>1;
      if((ref==_x)){
        res = true;
        break;
      }else if(_x < ref){
        if(nmid>0) idx -= nmid;
      }else{
        idx += (nmid>0)?(nmid):(1);
      }
      if(0==mid){
        break;
      }
      mid = nmid;
    }
  }
  return res;
}

//-----

/**
 * @brief ceil_log2_v1
 *
 * @param  x
 * @return
 */
template<typename T> constexpr T ceil_log2_v1(T _x){
  Compile::Guards::IsUnsigned<T>();

  //get number of bits divided by 2 of type T
  constexpr u8 const halfbits = sizeof(T)<<2;
  T res = 0;

  if(_x>0){
    //Mask with all bits set in the upper half and zeros in the lower
    T mask = Math::Boolean::Logic_Shift_L<T>(Math::Boolean::GETFULLMASK<T>(halfbits),halfbits);
    //init shift by halfbits
    u8 shift = halfbits;

    while(shift>1){
      if(_x&mask){
        res += shift;
      }
      shift >>= 1;
      mask ^= (mask >> shift);
    }

    if(_x&mask){
      res += shift;
    }
    mask ^= (mask >> 1);
    if(_x&mask){
      res += shift;
    }
   //mask ^= (mask >> 1);
    --res;
  }
  return res;
}

//-----

/**
 *
 */
template<typename T> u8 floor_log2_v1(T _x){
  Compile::Guards::IsUnsigned<T>();
  u8 res = 0;

  if(_x>0){
    //u8 bits = (sizeof(T)<<3);
    u8 bits = Math::Boolean::GETBITSOFTYPE<T>();
    T v = _x;

    while(bits>1){
      res <<= 1;
      bits >>= 1;
      //T mask = ((((T(1)<<(bits-1))-1)<<1)|1);
      T mask = Math::Boolean::GETFULLMASK<T>(bits);
      if(v > mask){
        res |= 1;
        v=mask&(v>>bits);
      }
    }
  }
  return res;
}


/*template<typename T> u8 log2c(T const _x){
  u8 res = 0;
  if(_x>0){
    T v = _x;
    while(!Math::Boolean::IS_ONEHOT<T>(v)){
      v = Math::Boolean::clr_rightmost_1bit<T>(v);
    }
  }
 u8 const bits = Math::Boolean::GETBITSOFTYPE<T>()>>1;
 T mask = Math::Boolean::GETFULLMASK<T>(bits);
 if(v>mask) res += bits;
}*/

template<typename T> u8 log2c(T const _x){
  Compile::Guards::IsUnsigned<T>();

  u8 res = 0;

  if(_x>0){
    //Make the highest set bit the lowest one
    auto br = Algorithms::Bitreverse::nibbleLut_methodV2<T>(_x);
    //Isolate the lowest bit set in Integer
    auto lbs = Math::Boolean::GET_LOWESTBIT_V3<T>(br);

    auto bits = Math::Boolean::GETBITSOFTYPE<T>()>>1;
    auto shift = bits;
    do{
      auto mask = Math::Boolean::GETMASKBIT<T>(shift);
      if(bits>1) bits >>= 1;
      if(mask>lbs){
        shift -= bits;
      }else if(mask<lbs){
        shift += bits;
      }else{
        res = Math::Boolean::GETBITSOFTYPE<T>()-bits;
      }
    }while(res==0);
  }
  return res;
}

//--------------------------------------------------

/**
 * ceil(log2)
 */
template<typename T> u8 ceil_log2_v2(T const val){
  Compile::Guards::IsUnsigned<T>();
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
template<typename T> u8 floor_log2_v2(T const val){
  Compile::Guards::IsUnsigned<T>();
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

//--------------------------------------------------

// Floor(log2(x))
template<typename T> u8 floor_log2_v3(T const _a){
  Compile::Guards::IsUnsigned<T>();
  auto const bytes = sizeof(T);
  T x = _a;
  x |= (x >> 1);
  x |= (x >> 2);
  x |= (x >> 4);
  if(2>=bytes){x |= (x >> 8);}
  if(4>=bytes){x |= (x >> 16);}
  if(8>=bytes){x |= (x >> 32);}
  return u8(Algorithms::CountBitsset::parallel<T>(x) - 1);
}

//--------------------------------------------------

[[deprecated]] s32 floorLog2_32(u32 const n);
[[deprecated]] s16 floorLog2_16(u16 const n);

//-----

[[deprecated]] u8 log2u32(u32 const _x);

//-----

u8 minilog2(u8 const _x);

//-----

} //namespace

} //namespace

#endif // LOG2_H
