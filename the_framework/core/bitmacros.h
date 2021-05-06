/******************************************************************************/
/** ----- Bit M A C R O S -----     Integer Bitmanipulation Macros           **/
/** if not stated otherwise:                                                 **/
/** Assume Unsigned Integer Numbers and Two'sCompliment Arithmethic          **/
/** developed , collected and / or implemented by                            **/
/** Danny Schneider, 2014-2021                                               **/
/**                                                                          **/
/** Sources & Ideas for Algorithms used here:                                **/
/** http://aggregate.org/MAGIC/                                              **/
/** http://graphics.stanford.edu/~seander/bithacks.html                      **/
/** http://gurmeet.net/puzzles/fast-bit-counting-routines/                   **/
/**                                                                          **/
/**                                                                          **/
/**                                                                          **/
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

#ifndef BYTEMACROS_H
#define BYTEMACROS_H

//--------------------------------------------------

#include <type_traits>
#include "dtypes.h"
#include "global_config.h"
#include "compile_guards.h"
#include "meta.h"

//--------------------------------------------------

//----- Macros
//      m... -> normal Macro
//      ma.. -> auto Assignment to first Operand

// --- Portable Bitmask for X Bits Generation ---
// => e.g. mBitMask(32) wont use shift 32,
// so its safe on a 32Bit Computer
#define mBitMask(_b) ((((1ULL<<((_b)-1))-1)<<1)|1ULL)

// --- Logic ---

#define mINVERT(_x)     (~(_x))
#define maINVERT(_x)    ((_x)~=(_x))

#define mXOR(_x,_y)     ((_x)^((_y)))
#define maXOR(_x,_y)    ((_x)^=((_y)))

#define mOR(_x,_y)      ((_x)|(_y))
#define maOR(_x,_y)     ((_x)|=(_y))

#define mAND(_x,_y)     ((_x)&(_y))
#define maAND(_x,_y)    ((_x)&=(_y))

#define mNAND(_x,_y)     (~mAND((_x),(_y)))
#define maNAND(_x,_y)    ((_x)=mNAND((_x),(_y)))

// --- Bit Manipulation ---

#define maSetBit(_v,_b) ((_v)|=(1U<<(_b)))
#define mGetBit(_v,_b)  ((_v)&(1U<<(_b)))
#define maClrBit(_v,_b) ((_v)&=~(1U<<(_b)))

// ---

#define maskBits(_x,_y)                   (mAND((_x),(_y)))
#define maskBitsExcept(_x,_y,_be)         (mAND(mAND((_x),(_y)),mINVERT(_be)))
#define maskTestBits(_x,_y,_b)            (mAND((_x),(_y))==(_b))
#define maskTestBitsExcept(_x,_y,_b,_be)  (maskBitsExcept(_x,_y,_be)==(_b))

// ---

#define maskBitsSet(_x,_y)                (maOR((_x),(_y)))
#define maskBitsSetExcept(_x,_y,_be)      (maOR((_x),mAND((_y),mINVERT(_be))))
#define maskBitsClear(_x,_y)              (maAND((_x),mINVERT(_y)))
#define maskBitsClearExcept(_x,_y,_be)    (maAND((_x),mINVERT(mAND((_y),mINVERT(_be)))))
#define maskBitsToggle(_x,_y)             (maXOR((_x),(_y)))
#define maskBitsToggleExcept(_x,_y,_be)   (maXOR((_x),mAND((_y),mINVERT(_be))))

// --- Shift Operations ---

#define mSHR(_v,_b)     ((_v)>>(_b))
#define maSHR(_v,_b)    ((_v)>>=(_b))

#define mSHL(_v,_b,_i)  (((_b)==0)?(_v):((((_v)<<(_b))&(0U-2))|(1U&(_i))))
#define maSHL(_v,_b,_i) ((_v)=(mSHL(_v,_b,_i)))

// --- Get / Change a Bit (to State i) ---

#define maSetBinary(_v,_b,_i) ((_v)=(((_v)&(~(1U<<(_b))))|((_i)<<(_b))))
#define mGetBinary(_v,_b)     (((_v)>>(_b))&1U)

// --- Word <--> Byte Access ---
#define mHByte(_v) (((_v)>>8)&0x00FFu)
#define mLByte(_v) ((_v)&0x00FFu)

#define mSwapByte(_w)    (mOR(mAND(mSHR((_w),8),mBitMask(8)),mSHL(mAND((_w),mBitMask(8)),8,0)))
#define mToWord(_b1,_b2) (mOR(mAND((_b1),mBitMask(8)),mSHL(mAND((_b2),mBitMask(8)),8,0)))

//--------------------------------------------------

namespace Math{

namespace Boolean{

//--------------------------------------------------

/**
 * number of bits of given Type T
 */
template<typename T> constexpr size_t GETBITSOFTYPE() noexcept{
  return (sizeof(T)<<3);
}

/**
 * number of nibbles of given Type T
 */
template<typename T> constexpr size_t GETNIBBLESOFTYPE() noexcept{
  return (sizeof(T)<<1);
}

/**
 * satturate "bits" at value of number of bits of given Type T
 */
template<typename T> constexpr size_t GETMAXBITS(size_t const bits=GETBITSOFTYPE<T>()) noexcept{
  Compile::Guards::IsInteger<T>();
  return (GETBITSOFTYPE<T>()<bits)?(GETBITSOFTYPE<T>()):(bits);
}

//--------------------------------------------------

/**
 * @brief Convert number of nibbles to number of bits
 */
template<typename T> constexpr size_t NIBBLES2BITS(size_t const nibbles=sizeof(T)<<1) noexcept{
  return (nibbles<<2);
}

/**
 * @brief Convert number of bits to number of nibbles to fit all bits in (ceil-behavouir)
 */
template<typename T> constexpr size_t BITS2NIBBLES(size_t const bits=GETBITSOFTYPE<T>()) noexcept{
  return (bits>>2)+(((bits&size_t(3))>0)?(1):(0));
}

//--------------------------------------------------

/**
 * Test Integer if it is Even (LSB==0)
 */
template<typename T> constexpr bool IS_EVEN(T const _x) noexcept{
  Compile::Guards::IsInteger<T>();
  return ((_x&T(1))==0);
}
/**
 * Test Integer if it is Odd (LSB==1)
 */
template<typename T> constexpr bool IS_ODD(T const _x) noexcept{
  Compile::Guards::IsInteger<T>();
  return ((_x&T(1))>0);
}

//--------------------------------------------------

/**
 * @brief GET_LOWESTBIT - Get Lowest Bit Set in an Integer (result is One Hot)
 *                        Fastest posibility to encode / calculate Priorities!!!
 * @return lowest bit set in integer (only the lowest bit set in result)
 */
template<typename T> constexpr T GET_LOWESTBIT(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return ((_x^(_x-1))&_x);
}
template<typename T> constexpr T GET_LOWESTBIT_V2(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return ((~(_x-1))&_x);
}
template<typename T> constexpr T GET_LOWESTBIT_V3(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (_x)&((~(_x))+1);
}

//----- Test for OneHot

/**
 * Is Integer a Power of 2 (is Integer One Hot encoded?)
 * returns true if non negative integer is power of two
 */
template<typename T> constexpr bool IS_ONEHOT(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (_x>0)?((_x&(_x-1))==0):(false);
}

//--------------------------------------------------

/**
 * starting with the highest bit set, set all lower bits in an Integer
 */
template<typename T> constexpr T set_all_lower_bits(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  T res = _x;
  constexpr u8 const bitsoftype = GETBITSOFTYPE<T>();
  u8 shift = 1;
  while(shift<bitsoftype){
    res |= res >> shift;
    shift <<= 1;
  }
  return res;
}

/**
 * For any _x get the next larger, one hot coded number (the next larger 2^x)
 */
template<typename T> constexpr T next_power_of_2(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  T res = _x-1;
  res = set_all_lower_bits<T>(res);
  return 1+res;
}

/**
 * @brief get_msb - Most Significant Bit set
 * @param _a
 * @return
 */
template<typename T> constexpr T get_msb(T const _a){
  Compile::Guards::IsUnsigned<T>();
  constexpr auto const bytes = sizeof(T);
  T x = _a;
  x |= (x >>  1);
  x |= (x >>  2);
  x |= (x >>  4);
  if(2>=bytes){x |= (x >>  8);} //u16
  if(4>=bytes){x |= (x >> 16);} //u32
  if(8>=bytes){x |= (x >> 32);} //u64
  return(x & ~(x >> 1));
}

/**
 *
 */
template<typename T> constexpr T right_propagate_rightmost_1bit(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (_x | (_x-1));
}

/**
 *
 */
template<typename T> constexpr T isolate_rightmost_0bit(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (~_x & (_x+1));
}

/**
 *
 */
template<typename T> constexpr T set_rightmost_0bit(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (_x | (_x+1));
}

/**
 *
 */
template<typename T> constexpr T get_rightmost_1bit(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  T const _y = (_x-1);
  return ((_x|_y)^_y);
}

/**
 *
 */
template<typename T> constexpr T clr_rightmost_1bit(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (_x & (_x-1));
}

//--------------------------------------------------

/**
 * Get Mask for single Bit 0..N-1
 * * !!!WARNING!!! GETMASKBIT<uAB>(AB) will not fit in type uAB
 *  0 - 1 -    1
 *  1 - 2 -   10
 *  2 - 4 -  100
 *  3 - 8 - 1000
 */
template<typename T> constexpr T GETMASKBIT(size_t bit) noexcept{
  Compile::Guards::IsInteger<T>();
  return T(1)<<(GETMAXBITS<T>(bit));
}

/**
 * if we have 4 bits, then the mask for the bit 4 is: 10000,
 * which is the decimal value of 16. And 4 bits allow to represent
 * a "space" of 16 different values
 *
 * !!!WARNING!!! BITSPACE<uAB>(AB) will not fit in type uAB
 * 0 -    1 = 1
 * 1 -   10 = 2
 * 2 -  100 = 4
 * 3 - 1000 = 8
 */
template<typename T> constexpr T BITSPACE(u8 bits) noexcept{
  Compile::Guards::IsInteger<T>();
  return GETMASKBIT<T>(bits);
}

/**
 * One Hot coded Mask --> highest Bit 0...N-1 Set only
 * Parameter: Bits of Mask
 * 0 -    0
 * 1 -    1
 * 2 -   10
 * 3 -  100
 */
template<typename T> constexpr T MASK_MSB(u8 bits=GETBITSOFTYPE<T>()) noexcept{
  Compile::Guards::IsInteger<T>();
  return (bits>0)?(BITSPACE<T>(bits-1)):(0);
}

/**
 * Overflow Safe set all Bits for space of x Bits 0..N
 * 0 -   0
 * 1 -   1
 * 2 -  11
 * 3 - 111
 */
template<typename T> constexpr T GETFULLMASK(T const bits) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (bits<2)?(bits):((((GETMASKBIT<T>(bits-1)-1)<<1)|1));
  //return (bits>1)?(((BITSPACE<T>(bits-1)-1)<<1)|1):(bits);
}

/**
 * Overflow Safe set all Bits for space of x Bits 1..N
 * 0 -   0
 * 1 -   1
 * 2 -  11
 * 3 - 111
 */
template<typename T> constexpr T GETFULLMASK_v2(T const _x) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (_x>0)?(right_propagate_rightmost_1bit<T>(GETMASKBIT<T>(_x-1))):(0);
}

/**
 * Overflow Safe Mask with all Bits Set
 * on a X Bit CPU X Bit Masks without Integer Overflow
 * Parameter: Bits of Mask
 */
/*template<typename T> [[deprecated]] T OFS_MAX(u8 const bits) noexcept{
  return (bits>0)?(((BITSPACE<T>(bits-1)-1)<<1)|1):(0);
}*/

//-----

/**
 * Apply Mask
 */
template<typename T> constexpr T MASKBITS(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return ((_x)&(_y));
}

//--------------------------------------------------

//----------------------------------------
// http://www.fefe.de/intof.html (modified/extended)
//----------------------------------------

//Overflow Safe Calculation of max. Unsigned Integer with x-Bits
template<typename T> constexpr T MAXUINT(u8 const bits) noexcept{
  Compile::Guards::IsUnsigned<T>();
//#define MAXUINT(_X) ((((1U<<((_x)-1))-1)<<1)+1)
  return (((T(1)<<(bits-1))-1)<<1)|1;
}

/**
 * Finding the minimum and maximum values for a given integer type
 */

/**
 * @brief - (highest positive Value /2) + 1 --> the MSB is set
 */
template<typename T> constexpr T __HALF_MAX_UNSIGNED() noexcept{
  Compile::Guards::IsUnsigned<T>();
//#define __HALF_MAX_UNSIGNED(type) (static_cast<type>(1)<<((sizeof(type)<<3)-1))
  return (T(1)<<((GETBITSOFTYPE<T>())-1));
}

/**
 * @brief - (highest positive Value /2) + 1 --> the Bit next to the sign is set
 */
template<typename T> constexpr T __HALF_MAX_SIGNED() noexcept{
  Compile::Guards::IsSigned<T>();
//#define __HALF_MAX_SIGNED(type)   (static_cast<type>(1)<<((sizeof(type)<<3)-2))
  return (T(1)<<((GETBITSOFTYPE<T>())-2));
}

/**
 * @brief - highest positive Value
 */
template<typename T> constexpr T __MAX_UNSIGNED() noexcept{
  Compile::Guards::IsUnsigned<T>();
//#define __MAX_UNSIGNED(type)      ((__HALF_MAX_UNSIGNED(type)<<1)+__HALF_MAX_UNSIGNED(type))
//return ((__HALF_MAX_UNSIGNED<T>()-1)<<1)+1;
  return MAXUINT<T>(GETBITSOFTYPE<T>());
}

/**
 * @brief
 */
template<typename T> constexpr T __MAX_SIGNED() noexcept{
  Compile::Guards::IsSigned<T>();
  using UT = typename std::make_unsigned<T>::type;
//#define __MAX_SIGNED(type)        (__HALF_MAX_SIGNED(type)-1+__HALF_MAX_SIGNED(type))
//return __HALF_MAX_SIGNED<T>()-1+__HALF_MAX_SIGNED<T>();
  return static_cast<T>(MAXUINT<UT>((GETBITSOFTYPE<T>())-1));
}

/**
 * @brief
 */
template<typename T> constexpr T __MIN_SIGNED() noexcept{
  Compile::Guards::IsSigned<T>();
  using UT = typename std::make_unsigned<T>::type;
//#define __MIN_SIGNED(type)        (-1-__MAX_SIGNED(type))
//return -1-__MAX_SIGNED<T>();
  return MASK_MSB<T>(static_cast<T>(GETBITSOFTYPE<UT>()));
}

/**
 * @brief
 */
template<typename T> constexpr T __MIN() noexcept{
  Compile::Guards::IsInteger<T>();
  using ST = typename std::make_signed<T>::type;
//#define __MIN(type) (static_cast<type>(-1) < ((1)?(__MIN_SIGNED(type)):(static_cast<type>(0))))
  return (T(-1)<((1))?(__MIN_SIGNED<ST>()):(T(0)));
}

/**
 * @brief
 */
template<typename T> constexpr T __MAX() noexcept{
  Compile::Guards::IsInteger<T>();
//#define __MAX(type) (static_cast<type>(~__MIN(type)))
  return T(~__MIN<T>());
}

//--------------------------------------------------

/**
 * Bitwise And
 */
template<typename T> constexpr T AND(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return ((_x)&(_y));
}

/**
 *Bitwise Or
 */
template<typename T> constexpr T OR(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return ((_x)|(_y));
}

/**
 *Bitwise Xor
 */
template<typename T> constexpr T XOR(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return ((_x)^(_y));
}

//--------------------------------------------------

/**
 * in _x set set bits from _y
 */
template<typename T> constexpr T SETBITS(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (OR<T>((_x),(_y)));
}

/**
 * in_x clear set bits from _y
 */
template<typename T> constexpr T CLRBITS(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (AND<T>((_x),~(_y)));
}

/**
 * bits set in _x and _y will be cleared, bits cleared in _x and _y will be set
 */
template<typename T> constexpr T TOGGLEBITS(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (XOR<T>((_x),(_y)));
}

/**
 * test if _x and _y are binary equal
 */
template<typename T> constexpr bool EQUAL(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (((_x)^(_y))==0);
}

/**
 * test if all bits in _y are set in _x
 */
template<typename T> constexpr bool TESTBITS(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return EQUAL<T>(AND<T>((_x),(_y)),_y);
}

//--------------------------------------------------

/**
 * @brief - ARITHSHL
 */
template<typename T> constexpr T ARITHSHL(T const _x, u8 const _y) noexcept{
  Compile::Guards::IsInteger<T>();
  return ((_x)<<(_y));
}

/**
 * @brief - ARITHSHR
 */
template<typename T> constexpr T ARITHSHR(T const _x, u8 const _y) noexcept{
  Compile::Guards::IsInteger<T>();
  return ((_x)>>(_y));
}

/**
 * @brief - ROTL
 */
template<typename T> constexpr T ROTL(T const _x, u8 const _y) noexcept{
  Compile::Guards::IsInteger<T>();
  constexpr auto const TBits = u8(Math::Boolean::GETBITSOFTYPE<T>());
  return (((_x)<<(_y))|((_x)>>(TBits-_y)));
}

/**
 * @brief - ROTR
 */
template<typename T> constexpr T ROTR(T const _x, u8 const _y) noexcept{
  Compile::Guards::IsInteger<T>();
  constexpr auto const TBits = u8(Math::Boolean::GETBITSOFTYPE<T>());
  return (((_x)>>(_y))|((_x)<<(TBits-_y)));
}

//--------------------------------------------------

/**
 * from _x extract field from position _lsb with length _len
 */
template<typename T> constexpr T GETVALUE(T const _x, T const _lsb, T const _len) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return (((_x)>>(_lsb))&GETFULLMASK<T>(_len));
}

/**
 * Replace Field - Replace a field in x with same field from y
 */
template<typename T> constexpr T REPLFIELD(T const _x, T const _y, T const _lsb, T const _len) noexcept{
  Compile::Guards::IsUnsigned<T>();
  T const mask = ~(GETFULLMASK<T>(_len)<<_lsb);
  return (_y)|(_x&mask);
}

/**
 * in _x replace field from position _lsb with length _len with data from _y
 */
template<typename T> constexpr auto SETVALUE(T& _x, T const _y, T const _lsb, T const _len) noexcept{
  Compile::Guards::IsUnsigned<T>();
  T shift_y = ARITHSHL<T>(_y,_lsb);
  return _x=REPLFIELD<T>(_x,shift_y,_lsb,_len);
}

//--------------------------------------------------

/**
 *
 */
template<typename T> constexpr auto RANGELIMIT(T const _x, T const _y) noexcept{
  Compile::Guards::IsUnsigned<T>();
  return ((_x)%(_y));
}

//--------------------------------------------------

/**
 * Zweierkomplement - Two's Complement
 */
template<typename T> constexpr T ZQ(T const _x) noexcept{
  Compile::Guards::IsInteger<T>();
  return ((~(_x))+1);
}

template<typename T> using unsigned_t = typename std::make_unsigned<T>::type;

/**
 * if integer number is negative, get the same number with positiv sign
 */
template<typename T> constexpr auto INTABS(T const _x) noexcept -> unsigned_t<T>{
  Compile::Guards::IsInteger<T>();
  return static_cast<unsigned_t<T>>((_x<0)?(ZQ<T>(_x)):(_x));
}

/**
 * Absolute Value of an Integer
 * Code is Architecture dependent
 */
template<typename T> constexpr auto INTABS_V2(T const _x) noexcept -> unsigned_t<T>{
  Compile::Guards::IsInteger<T>();
  unsigned_t<T> res = static_cast<unsigned_t<T>>(_x); // the result goes here
  if(_x<0){
    constexpr u8 shift_by = Math::Boolean::GETBITSOFTYPE<T>()-1;
    T const mask = _x >> shift_by; //Sign as Mask
    res = static_cast<unsigned_t<T>>((_x + mask) ^ mask);    //Calc Absolute
  }
  return res;
}

template<typename T> constexpr auto INTABS_V3(T const _x) noexcept -> unsigned_t<T>{
  Compile::Guards::IsInteger<T>();
  constexpr auto const shift_by = GETBITSOFTYPE<T>() -1;
  T const mask = ARITHSHR<T>(_x,shift_by); //Use Signbit as mask
  return ((_x + mask)^mask);               //Calculate Absolute
}

//--------------------------------------------------

//Alternate Versions

#if dUSE_ALTVERSIONS>0

/**
 * Get Lowest Bit Set in an Integer (One Hot)
 * Fast posibility to encode / calculate Priorities!!!
 */
template<typename T> constexpr T lowest_one_set(T const _x) noexcept{
  return ((_x)&((~(_x))+1));
}

//--------------------------------------------------

/**
 * Is Integer a Power of 2 (is Integer One Hot encoded?)
 */
template<typename T> constexpr bool is_power_of_2(T const _x) noexcept{
  return ((((_x)&((_x)-1))==0)?(true):(false));
}

//--------------------------------------------------

#endif

//--------------------------------------------------

} //namespace

} //namespace

#endif // BYTEMACROS_H
