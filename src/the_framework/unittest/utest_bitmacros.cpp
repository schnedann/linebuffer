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

/****************************************
 * Includes
 ****************************************/
#include <iostream>
#include <iomanip>
#include <random>

#include "catch.hpp"

#include "dtypes.h"
#include "bitmacros.h"
#include "math_discrete.h"
#include "simple_hash_fct.h"

/****************************************
 * Defines
 ****************************************/



/****************************************
 * Namespaces
 ****************************************/

using namespace std;

/****************************************
 * local Prototypes
 ****************************************/



/****************************************
 * Global Constants
 ****************************************/



/****************************************
 * Typedefs
 ****************************************/



/****************************************
 * Code
 ****************************************/

TEST_CASE("Math::Boolean","[boolean]"){

  SECTION("1.1 - IS_EVEN not IS_ODD"){
    auto const ref = u32(GENERATE(take(1000, filter([](u32 _x) {return (0==(_x%2));}, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>())))));
    CAPTURE( ref );
    REQUIRE(  Math::Boolean::IS_EVEN<u32>(ref) );
    REQUIRE( !Math::Boolean::IS_ODD<u32>(ref) );
  }
  SECTION("1.2 - IS_ODD not IS_EVEN"){
    auto const ref = u32(GENERATE(take(1000, filter([](u32 _x) {return (0!=(_x%2));}, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>())))));
    CAPTURE( ref );
    REQUIRE( !Math::Boolean::IS_EVEN<u32>(ref) );
    REQUIRE(  Math::Boolean::IS_ODD<u32>(ref) );
  }

//--------------------------------------------------

  SECTION("2 - Math::Boolean::next_power_of_2<u64>()"){
    u64 mask = 1;
    REQUIRE( 0 == Math::Boolean::next_power_of_2<u64>(0) );
    do{
      CAPTURE( mask );
      REQUIRE( ((1==mask)?(1):(mask+1)) == Math::Boolean::next_power_of_2<u64>(mask) );
      mask = (mask<<1) | 1;
    }while(mask != Math::Boolean::GETFULLMASK<u64>(64));
  }

//--------------------------------------------------

  SECTION("3a - IS_ONEHOT"){
    auto const ref = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    bool is_OH = (ref == Math::Boolean::next_power_of_2<u32>(ref));
    if(is_OH){
      REQUIRE(Math::Boolean::IS_ONEHOT<u32>(ref));
    }else{
      REQUIRE(!Math::Boolean::IS_ONEHOT<u32>(ref));
    }
  }

  SECTION("3b - IS_ONEHOT"){
    for(u8 ii=0; ii<64; ++ii){
      auto oh = Math::Boolean::GETMASKBIT<u64>(ii);
      CAPTURE( ii );
      CAPTURE( oh );
      REQUIRE(  Math::Boolean::IS_ONEHOT<u64>(oh)   );
      if(oh>1) REQUIRE( !Math::Boolean::IS_ONEHOT<u64>(oh+1) );
      if(oh>3) REQUIRE( !Math::Boolean::IS_ONEHOT<u64>(oh-1) );
    }
  }

//--------------------------------------------------

  SECTION("4a - GET_LOWESTBIT"){
    auto const ii = u32(GENERATE(take(2500, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    u32 reference;
    for(u8 ij=0; ij<32; ++ij){
      auto bit = Math::Boolean::GETMASKBIT<u32>(ij); //Bit at position ij
      reference = Math::Boolean::AND<u32>(ii,bit);   //>0 if bit exists in ii
      if(reference>0) break;
    }
    auto tmp = Math::Boolean::GET_LOWESTBIT<u32>(ii);
    CAPTURE( ii );
    REQUIRE( reference == tmp );
  }

  SECTION("4b - GET_LOWESTBIT"){
    for(u32 ii=1; ii<1000000; ++ii){
      u32 reference;
      for(u8 ij=0; ij<32; ++ij){
        auto bit = Math::Boolean::GETMASKBIT<u32>(ij);
        reference = Math::Boolean::AND<u32>(ii,bit);
        if(reference>0) break;
      }
      auto tmp1 = Math::Boolean::GET_LOWESTBIT<u32>(ii);
      auto tmp2 = Math::Boolean::GET_LOWESTBIT_V2<u32>(ii);
      auto tmp3 = Math::Boolean::GET_LOWESTBIT_V3<u32>(ii);
      auto tmp4 = Math::Boolean::get_rightmost_1bit<u32>(ii);
      CAPTURE( ii );
      REQUIRE( reference == tmp1 );
      REQUIRE( tmp1 == tmp2 );
      REQUIRE( tmp2 == tmp3 );
      REQUIRE( tmp3 == tmp4 );
      REQUIRE( tmp4 == reference );
      REQUIRE( Math::Boolean::IS_ONEHOT<u32>(tmp1) );
    }
  }

//--------------------------------------------------

  SECTION("5 - GETMASKBIT"){
    u32 reference = 1;
    for(u8 ii=0; ii<32; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETMASKBIT<u32>(ii) );
      reference <<=1;
    }
  }

//--------------------------------------------------

  SECTION("6a - GETFULLMASK / GETFULLMASK_v2"){
    REQUIRE( 0 == Math::Boolean::GETFULLMASK<u32>(0) );
    u32 reference = 1;
    for(u8 ii=1; ii<33; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETFULLMASK<u32>(ii) );
      REQUIRE( reference == Math::Boolean::GETFULLMASK_v2<u32>(ii) );
      reference = (reference<<1)|1;
    }
  }

  SECTION("6b - GETFULLMASK 2/3"){
    REQUIRE( 0 == Math::Boolean::GETFULLMASK<u32>(0) );
    REQUIRE( 0 == Math::Boolean::GETFULLMASK_v2<u32>(0) );
    /*u32 reference = 1;
    for(u8 ii=1; ii<33; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETFULLMASK<u32>(ii) );

      reference = (reference<<1)|1;
    }*/
  }

  /*SECTION("6c - GETFULLMASK 3/3"){
    u32 reference = 1;
    for(u8 ii=1; ii<33; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETFULLMASK<u32>(ii) );
      //REQUIRE( reference == Math::Boolean::OFS_MAX<u32>(ii) );
      reference = (reference<<1)|1;
    }
  }*/

  SECTION("7a - REPLFIELD / GETVALUE"){
    u64 r1 = 0x0123456789ABCDEFull;
    u64 r2 = 0x01234AFFEDEADDEFull;   //in from start(@LSB!) length
    auto tmp = Math::Boolean::REPLFIELD<u64>(r2,r1,12,32);
    REQUIRE( r1 == tmp );
    REQUIRE( r1 != r2 );
    REQUIRE( 0xAFFEDEADull == Math::Boolean::GETVALUE<u64>(r2,12,32) );
    REQUIRE( Math::Boolean::GETVALUE<u64>(r1,44,20) == Math::Boolean::GETVALUE<u64>(r2,44,20) );
  }

  SECTION("7b - SETVALUE / GETVALUE"){
    u64 r1 = 0x0123456789ABCDEFull;
    u64 r2 = 0x01234AFFEDEADDEFull;
    auto tmp = Math::Boolean::SETVALUE<u64>(r2,Math::Boolean::GETVALUE<u64>(r1,12,32),12,32);
    REQUIRE( r1 == tmp );
    REQUIRE( r1 == r2 );
    REQUIRE( 0xAFFEDEADull != Math::Boolean::GETVALUE<u64>(r2,12,32) );
    REQUIRE( Math::Boolean::GETVALUE<u64>(r1,44,20) == Math::Boolean::GETVALUE<u64>(r2,44,20) );
    REQUIRE( Math::Boolean::GETVALUE<u64>(r1,12,32) == Math::Boolean::GETVALUE<u64>(r2,12,32) );
  }

  SECTION("8 - ZQ / INTABS - 1/2"){
    //u64 uref = 1;
    s64 sref = 1;
    for(s64 ii=-1; ii>-1000000; --ii){
      REQUIRE( sref++ == s64(Math::Boolean::ZQ<u64>(u64(ii))) );
      //REQUIRE( uref++ == Math::Boolean::INTABS<s64>(ii) );
    }
  }

  SECTION("8 - ZQ / INTABS - 2/2"){
    auto const tmp = u32(GENERATE(take(2500, random(0, Math::Boolean::__MAX<s32>()))));
    auto ref =  tmp;
    auto dut = 0-tmp;

    CAPTURE(tmp);
    CAPTURE(ref);
    CAPTURE(dut);

    auto ref3 = Math::Boolean::INTABS_V3<s32>(dut);
    auto ref2 = Math::Boolean::INTABS_V2<s32>(dut);
    auto  res = Math::Boolean::INTABS<s32>(dut);

    REQUIRE(  ref == res );
    REQUIRE( ref2 == res );
    REQUIRE( ref3 == res );
  }

  SECTION("9 - multiply_low_part / multiply_high_part"){
    auto const ii = u32(GENERATE(take(100, random(0, s32(Math::Boolean::__MAX<u16>())))));
    auto const ij = u32(GENERATE(take(100, random(0, s32(Math::Boolean::__MAX<u16>())))));
    CAPTURE(ii);
    CAPTURE(ij);

    u32 ref = ii*ij;
    CAPTURE(ref);

    REQUIRE( u16(ref)     == Math::Discrete::multiply_low_part<u16>(u16(ii),u16(ij)) );
    REQUIRE( u16(ref>>16) == Math::Discrete::multiply_high_part<u16>(u16(ii),u16(ij)) );
  }

  SECTION("10 - midsquare_64"){
    u8 collect = 0;
    for(u16 ii=0; ii<256; ++ii){
      collect |= u8(Math::Hashing::midsquare_64<u16>(ii,8));
    }
    REQUIRE( Math::Boolean::GETFULLMASK<u8>(8) == collect );
  }

  SECTION("11 - GETMAXBITS"){
    for(u16 ii=0; ii<256; ++ii){
      u8 ref8 = (ii>8)?(8):(ii);
      u8 ref16 = (ii>16)?(16):(ii);
      u8 ref32 = (ii>32)?(32):(ii);
      u8 ref64 = (ii>64)?(64):(ii);

      REQUIRE( ref8 ==Math::Boolean::GETMAXBITS<u8>(ii) );
      REQUIRE( ref16==Math::Boolean::GETMAXBITS<u16>(ii) );
      REQUIRE( ref32==Math::Boolean::GETMAXBITS<u32>(ii) );
      REQUIRE( ref64==Math::Boolean::GETMAXBITS<u64>(ii) );
    }
    /*REQUIRE( 7==Math::Boolean::GETMAXBITS<u8>(7) );
    REQUIRE( 8==Math::Boolean::GETMAXBITS<u8>(8) );
    REQUIRE( 8==Math::Boolean::GETMAXBITS<u8>(9) );

    REQUIRE( 15==Math::Boolean::GETMAXBITS<u16>(15) );
    REQUIRE( 16==Math::Boolean::GETMAXBITS<u16>(16) );
    REQUIRE( 16==Math::Boolean::GETMAXBITS<u16>(17) );*/
  }

  SECTION("12 - BITSPACE"){
    u64 ref = 1;
    for(u8 ii=0; ii<32; ++ii){
      REQUIRE( ref==Math::Boolean::BITSPACE<u64>(ii) );
      ref <<= 1;
    }
  }

  SECTION("13 - MASK_MSB"){
    u64 ref = 1;
    for(u8 ii=1; ii<64; ++ii){
      REQUIRE( ref==Math::Boolean::MASK_MSB<u64>(ii) );
      ref <<= 1;
    }
  }

//--------------------------------------------------

  SECTION("14a - set_rightmost_0bit"){
    u64 mask = 2;
    u64 ref  = 1;
    do{
      CAPTURE( mask );
      CAPTURE( ref );
      REQUIRE( (ref|mask) == Math::Boolean::set_rightmost_0bit<u64>(mask) );
      mask <<= 1;
      mask  |= 1;
       ref <<= 1;
    }while(mask != Math::Boolean::GETFULLMASK<u64>(64));
  }

  SECTION("14b - set_rightmost_0bit"){
    u64 mask = 1;
    u64 ref  = 1;
    do{
      CAPTURE( mask );
      if(1==mask){
        REQUIRE( 3 == Math::Boolean::set_rightmost_0bit<u64>(mask) );
      }else{
        REQUIRE( (ref|mask) == Math::Boolean::set_rightmost_0bit<u64>(mask) );
      }
      mask <<= 1;
    }while(mask>0);
  }

  SECTION("15 - get_rightmost_1bit"){
    u64 mask = Math::Boolean::GETFULLMASK<u64>(64);
    u64  ref = 1;
    do{
      CAPTURE( mask );
      REQUIRE( ref == Math::Boolean::get_rightmost_1bit<u64>(mask) );
      mask <<= 1;
       ref <<= 1;
    }while(mask>0);
  }

  SECTION("16 - clr_rightmost_1bit"){
    u64 mask = Math::Boolean::GETFULLMASK<u64>(64);
    u64  ref = Math::Boolean::GETFULLMASK<u64>(64)<<1;
    do{
      CAPTURE( mask );
      REQUIRE( ref == Math::Boolean::clr_rightmost_1bit<u64>(mask) );
      mask <<= 1;
       ref <<= 1;
    }while(mask>0);
  }

  SECTION("17a - right_propagate_rightmost_1bit"){
    u64 mask = 5<<1;
    u64  ref = mask | 1;
    do{
      REQUIRE( ref == Math::Boolean::right_propagate_rightmost_1bit<u64>(mask) );
      mask <<= 1;
      ref = (ref<<1) | 1;
    }while((u64(5)<<61)!=(mask&(u64(5)<<61)));
  }

  SECTION("17b - Set all lower Bits"){
    u64 mask = 1;
    u64 reference = mask;
    while(mask>0){
      REQUIRE( reference == Math::Boolean::set_all_lower_bits<u64>(mask));
      mask <<=1;
      reference |= mask;
    }
  }

//--------------------------------------------------

  SECTION("19 - GETBITSOFTYPE / GETNIBBLESOFTYPE / NIBBLES2BITS"){
    REQUIRE(  8 == Math::Boolean::GETBITSOFTYPE<s8>());
    REQUIRE( 16 == Math::Boolean::GETBITSOFTYPE<s16>());
    REQUIRE( 32 == Math::Boolean::GETBITSOFTYPE<s32>());
    REQUIRE( 64 == Math::Boolean::GETBITSOFTYPE<s64>());

    REQUIRE(  8 == Math::Boolean::GETBITSOFTYPE<u8>());
    REQUIRE( 16 == Math::Boolean::GETBITSOFTYPE<u16>());
    REQUIRE( 32 == Math::Boolean::GETBITSOFTYPE<u32>());
    REQUIRE( 64 == Math::Boolean::GETBITSOFTYPE<u64>());

    REQUIRE( 32 == Math::Boolean::GETBITSOFTYPE<float>());
    REQUIRE( 64 == Math::Boolean::GETBITSOFTYPE<double>());

    //---

    REQUIRE( Math::Boolean::NIBBLES2BITS<u8>()  == Math::Boolean::GETBITSOFTYPE<u8>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s8>()  == Math::Boolean::GETBITSOFTYPE<s8>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<u16>() == Math::Boolean::GETBITSOFTYPE<u16>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s16>() == Math::Boolean::GETBITSOFTYPE<s16>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<u32>() == Math::Boolean::GETBITSOFTYPE<u32>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s32>() == Math::Boolean::GETBITSOFTYPE<s32>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<u64>() == Math::Boolean::GETBITSOFTYPE<u64>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s64>() == Math::Boolean::GETBITSOFTYPE<s64>() );

    //---

    REQUIRE( Math::Boolean::NIBBLES2BITS<u8>(Math::Boolean::GETNIBBLESOFTYPE<u8>())   == Math::Boolean::GETBITSOFTYPE<u8>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s8>(Math::Boolean::GETNIBBLESOFTYPE<s8>())   == Math::Boolean::GETBITSOFTYPE<s8>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<u16>(Math::Boolean::GETNIBBLESOFTYPE<u16>()) == Math::Boolean::GETBITSOFTYPE<u16>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s16>(Math::Boolean::GETNIBBLESOFTYPE<s16>()) == Math::Boolean::GETBITSOFTYPE<s16>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<u32>(Math::Boolean::GETNIBBLESOFTYPE<u32>()) == Math::Boolean::GETBITSOFTYPE<u32>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s32>(Math::Boolean::GETNIBBLESOFTYPE<s32>()) == Math::Boolean::GETBITSOFTYPE<s32>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<u64>(Math::Boolean::GETNIBBLESOFTYPE<u64>()) == Math::Boolean::GETBITSOFTYPE<u64>() );
    REQUIRE( Math::Boolean::NIBBLES2BITS<s64>(Math::Boolean::GETNIBBLESOFTYPE<s64>()) == Math::Boolean::GETBITSOFTYPE<s64>() );
  }

//--------------------------------------------------

  SECTION("20 - GETMAXBITS"){
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<u64>(); ++ii){
      REQUIRE( ((ii< 8)?(ii):( 8)) == Math::Boolean::GETMAXBITS<u8>(ii));
      REQUIRE( ((ii<16)?(ii):(16)) == Math::Boolean::GETMAXBITS<u16>(ii));
      REQUIRE( ((ii<32)?(ii):(32)) == Math::Boolean::GETMAXBITS<u32>(ii));
      REQUIRE( ((ii<64)?(ii):(64)) == Math::Boolean::GETMAXBITS<u64>(ii));
    }
  }

//--------------------------------------------------

  SECTION("xx - NIBBLES2BITS"){
    REQUIRE( 0 == Math::Boolean::BITS2NIBBLES<void>(0) );
    size_t ref = 1;
    for(u16 ii=1; ii<64; ++ii){
      CAPTURE(ii);
      REQUIRE( ref == Math::Boolean::BITS2NIBBLES<void>(ii) );
      if(0==(ii%4)){
        ++ref;
      }
    }
  }

//--------------------------------------------------

  SECTION("21a - minimum and maximum values for a given integer type"){
    using dut_t = u8;
    static constexpr dut_t const min  = 0;
    static constexpr dut_t const max  = 255U;
    static constexpr dut_t const half = 128U;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_UNSIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_UNSIGNED<dut_t>());
  }
  SECTION("21b - minimum and maximum values for a given integer type"){
    using dut_t = u16;
    static constexpr dut_t const min  = 0;
    static constexpr dut_t const max  = 65535U;
    static constexpr dut_t const half = 32768U;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_UNSIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_UNSIGNED<dut_t>());
  }
  SECTION("21c - minimum and maximum values for a given integer type"){
    using dut_t = u32;
    static constexpr dut_t const min  = 0;
    static constexpr dut_t const max  = 4294967295UL;
    static constexpr dut_t const half = 2147483648UL;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_UNSIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_UNSIGNED<dut_t>());
  }
  SECTION("21d - minimum and maximum values for a given integer type"){
    using dut_t = u64;
    static constexpr dut_t const min  = 0;
    static constexpr dut_t const max  = 0xFFFFFFFFFFFFFFFFULL;
    static constexpr dut_t const half = 0x8000000000000000ULL;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_UNSIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_UNSIGNED<dut_t>());
  }

  SECTION("21e - minimum and maximum values for a given integer type"){
    using dut_t = s8;
    static constexpr dut_t const min  = -128;
    static constexpr dut_t const max  = 127;
    static constexpr dut_t const half = 64;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(min == Math::Boolean::__MIN_SIGNED<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_SIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_SIGNED<dut_t>());
  }
  SECTION("21f - minimum and maximum values for a given integer type"){
    using dut_t = s16;
    static constexpr dut_t const min  = -32768;
    static constexpr dut_t const max  = 32767;
    static constexpr dut_t const half = 16384;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(min == Math::Boolean::__MIN_SIGNED<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_SIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_SIGNED<dut_t>());
  }
  SECTION("21g - minimum and maximum values for a given integer type"){
    using dut_t = s32;
    static constexpr dut_t const min  = -2147483648;
    static constexpr dut_t const max  = 2147483647;
    static constexpr dut_t const half = 1073741824;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(min == Math::Boolean::__MIN_SIGNED<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_SIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_SIGNED<dut_t>());
  }
  SECTION("21h - minimum and maximum values for a given integer type"){
    using dut_t = s64;
    static constexpr dut_t const min  = dut_t(0x8000000000000000LL);
    static constexpr dut_t const max  = dut_t(0x7FFFFFFFFFFFFFFFLL);
    static constexpr dut_t const half = 0x4000000000000000LL;
    REQUIRE(min == Math::Boolean::__MIN<dut_t>());
    REQUIRE(min == Math::Boolean::__MIN_SIGNED<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX<dut_t>());
    REQUIRE(max == Math::Boolean::__MAX_SIGNED<dut_t>());
    REQUIRE(half == Math::Boolean::__HALF_MAX_SIGNED<dut_t>());
  }

//--------------------------------------------------

  SECTION("22 - Math::Boolean::get_msb<u8>() 1/4"){
    using x_t = u8;
    x_t ref  = 1;
    x_t mask = 1;
    REQUIRE( 0 == Math::Boolean::get_msb<x_t>(0) );
    do{
      CAPTURE( mask );
      REQUIRE( ref == Math::Boolean::get_msb<x_t>(mask) );
      mask = (mask<<1) | 1;
      ref <<= 1;
    }while(mask != Math::Boolean::GETFULLMASK<x_t>(Math::Boolean::GETBITSOFTYPE<x_t>()));
  }
  SECTION("22 - Math::Boolean::get_msb<u16>() 2/4"){
    using x_t = u16;
    x_t ref  = 1;
    x_t mask = 1;
    REQUIRE( 0 == Math::Boolean::get_msb<x_t>(0) );
    do{
      CAPTURE( mask );
      REQUIRE( ref == Math::Boolean::get_msb<x_t>(mask) );
      mask = (mask<<1) | 1;
      ref <<= 1;
    }while(mask != Math::Boolean::GETFULLMASK<x_t>(Math::Boolean::GETBITSOFTYPE<x_t>()));
  }
  SECTION("22 - Math::Boolean::get_msb<u8>() 3/4"){
    using x_t = u32;
    x_t ref  = 1;
    x_t mask = 1;
    REQUIRE( 0 == Math::Boolean::get_msb<x_t>(0) );
    do{
      CAPTURE( mask );
      REQUIRE( ref == Math::Boolean::get_msb<x_t>(mask) );
      mask = (mask<<1) | 1;
      ref <<= 1;
    }while(mask != Math::Boolean::GETFULLMASK<x_t>(Math::Boolean::GETBITSOFTYPE<x_t>()));
  }
  SECTION("22 - Math::Boolean::get_msb<u8>() 4/4"){
    using x_t = u64;
    x_t ref  = 1;
    x_t mask = 1;
    REQUIRE( 0 == Math::Boolean::get_msb<x_t>(0) );
    do{
      CAPTURE( mask );
      REQUIRE( ref == Math::Boolean::get_msb<x_t>(mask) );
      mask = (mask<<1) | 1;
      ref <<= 1;
    }while(mask != Math::Boolean::GETFULLMASK<x_t>(Math::Boolean::GETBITSOFTYPE<x_t>()));
  }

//--------------------------------------------------

}
