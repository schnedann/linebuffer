#ifndef BITREVERSE_H
#define BITREVERSE_H

#include <array>

#include "dtypes.h"
#include "bitmacros.h"
#include "meta.h"
#include "compile_guards.h"

namespace Algorithms {

namespace Bitreverse {

/**
 * @brief simple_method - Bitreverse of an number
 *        Copy Bit by Bit with simple masks
 */
template<typename T> T simple_method(T const _v, u8 const bits=Math::Boolean::GETBITSOFTYPE<T>()) noexcept{
  Compile::Guards::IsUnsigned<T>();
  auto const msb_mask = Math::Boolean::MASK_MSB<T>(bits);
  T _x = _v;
  T res = 0;
  for(size_t ii=0; ii<bits; ++ii){
    if(Math::Boolean::TESTBITS<>(_x,msb_mask)){
      res = Math::Boolean::OR<>(res,Math::Boolean::GETMASKBIT<T>(ii));
    }
    _x = Math::Boolean::Logic_Shift_L<T>(_x,1);
  }
  return res;
}

/**
 * for all Bit do x=(x_-1)*2+(LSB>0)?(1):(0) with x_inti=0;
 */
template<typename T> T numerical_method(T const _v, u8 const bits=Math::Boolean::GETBITSOFTYPE<T>()) noexcept{
  Compile::Guards::IsUnsigned<T>();

  auto const mask = T(1);
  auto v_tmp = _v;

  T res = 0;
  //sum up the bitreverse
  for(u8 ii=0; ii<bits; ++ii){
    auto const next_bit = Math::Boolean::MASKBITS<T>(v_tmp,mask);
    v_tmp = Math::Boolean::Logic_Shift_R<T>(v_tmp,1);
    res = Math::Boolean::OR<T>(Math::Boolean::Logic_Shift_L<T>(res,1),next_bit);
  }
  return res;
}

/**
 * @brief maskshift_method - Swap bits with two moving masks
 *                           much like simple_method, but copy 2 bits at once
 */
template<typename T> T maskshift_method(T const _v, u8 const bits=Math::Boolean::GETBITSOFTYPE<T>()) noexcept{
  Compile::Guards::IsUnsigned<T>();
  T res = 0;
  T lmask = Math::Boolean::MASK_MSB<T>(bits);
  T rmask = 1;

  //until Masks meet in the middle of the number
  while(lmask >= rmask){
    res |= (_v&lmask)?(rmask):(0);
    res |= (_v&rmask)?(lmask):(0);
    lmask >>= 1;
    rmask <<= 1;
  }
  return res;
}

/**
 * @brief maskshift_method - Swap bits with two moving masks
 *                           much like simple_method, but copy 2 bits at once
 */
template<typename T> T maskshift_methodV2(T const _x, u8 const bits=Math::Boolean::GETBITSOFTYPE<T>()){
  Compile::Guards::IsUnsigned<T>();
  auto mask_lsb = T(1);
  auto mask_msb = Math::Boolean::MASK_MSB<T>(bits);
  T res = 0;
  while(mask_msb >= mask_lsb){
    if(Math::Boolean::TESTBITS<T>(_x,mask_lsb)){
      res = Math::Boolean::OR<T>(res,mask_msb);
    }
    if(Math::Boolean::TESTBITS<T>(_x,mask_msb)){
      res = Math::Boolean::OR<T>(res,mask_lsb);
    }
    mask_lsb = Math::Boolean::Logic_Shift_L<T>(mask_lsb,1);
    mask_msb = Math::Boolean::Logic_Shift_R<T>(mask_msb,1);
  }
  return res;
}

//--- nibble based methods

/**
 * @brief nibbleLut_method - Bitreverse of an number by nibblewise conversion
 *                           Copy 4Bits at once
 */
template<typename T> T nibbleLut_method(T const _v, u8 const nibbles=(sizeof(T)<<1)) noexcept{
  Compile::Guards::IsUnsigned<T>();
  //                       0  1  2  3  4  5  6  7
  std::array<T,16> const LUT = { 0, 8, 4,12, 2,10, 6,14,
                                 1, 9, 5,13, 3,11, 7,15};
  constexpr auto const mask = Math::Boolean::GETFULLMASK<T>(4);
  T res = 0;
  //For all nibbles do
  for(u8 ii=0; ii<nibbles; ++ii){
    //extract nibble and use it as LUT Index
    auto shift_by = (ii<<2); //for nibble shift by bits
    auto lut_idx = Math::Boolean::Logic_Shift_R<T>(_v,shift_by);
         lut_idx = Math::Boolean::MASKBITS<T>(lut_idx,mask);
    //Bitreverse of Nibble
    T tmp = LUT[lut_idx];
    //Move nibble to final position
    auto shift_to = (((nibbles-1)-ii)<<2);
    tmp = Math::Boolean::Logic_Shift_L(tmp,shift_to);
    //Blend the converted nibble and the result
    res = Math::Boolean::OR<T>(res,tmp);
  }
  return res;
}

/**
 * @brief nibbleLut_method - Bitreverse of an number by nibblewise conversion
 *                           Copy 4Bits at once
 */
template<typename T> T nibbleLut_methodV2(T const _x, u8 const nibbles=(sizeof(T)<<1)){
  Compile::Guards::IsUnsigned<T>();
  //                       0  1  2  3  4  5  6  7
  std::array<T,16> LUT = { 0, 8, 4,12, 2,10, 6,14,
                           1, 9, 5,13, 3,11, 7,15};
  constexpr static size_t const nibblesize = 4;
  auto const nibblebits = (nibbles<<2);
  u8 pos = 0;
  T res = 0;

  while(pos<nibblebits){
    T tmp = Math::Boolean::GETVALUE<T>(_x,pos,nibblesize);
    size_t rpos = nibblebits-(4+pos);
    T revnib = LUT[tmp];
    res = Math::Boolean::OR<T>(res,Math::Boolean::Logic_Shift_L<T>(revnib,rpos));
    pos += nibblesize;
  }
  return res;
}

} //namespace

} //namespace


#endif // BITREVERSE_H
