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

  SECTION("2 - IS_ONEHOT"){
    auto const ref = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    bool is_OH = (ref == Math::Boolean::next_power_of_2<u32>(ref));
    if(is_OH){
      REQUIRE(Math::Boolean::IS_ONEHOT<u32>(ref));
    }else{
      REQUIRE(!Math::Boolean::IS_ONEHOT<u32>(ref));
    }
  }

  SECTION("3 - GET_LOWESTBIT"){
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

  SECTION("4 - GETMASKBIT"){
    u32 reference = 1;
    for(u8 ii=0; ii<32; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETMASKBIT<u32>(ii) );
      reference <<=1;
    }
  }

  SECTION("5a - GETFULLMASK / GETFULLMASK_v2"){
    REQUIRE( 0 == Math::Boolean::GETFULLMASK<u32>(0) );
    u32 reference = 1;
    for(u8 ii=1; ii<33; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETFULLMASK<u32>(ii) );
      REQUIRE( reference == Math::Boolean::GETFULLMASK_v2<u32>(ii) );
      reference = (reference<<1)|1;
    }
  }

  SECTION("5b - GETFULLMASK 2/3"){
    REQUIRE( 0 == Math::Boolean::GETFULLMASK<u32>(0) );
    REQUIRE( 0 == Math::Boolean::GETFULLMASK_v2<u32>(0) );
    /*u32 reference = 1;
    for(u8 ii=1; ii<33; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETFULLMASK<u32>(ii) );

      reference = (reference<<1)|1;
    }*/
  }

  /*SECTION("5c - GETFULLMASK 3/3"){
    u32 reference = 1;
    for(u8 ii=1; ii<33; ++ii){
      CAPTURE( ii );
      REQUIRE( reference == Math::Boolean::GETFULLMASK<u32>(ii) );
      //REQUIRE( reference == Math::Boolean::OFS_MAX<u32>(ii) );
      reference = (reference<<1)|1;
    }
  }*/

  SECTION("6a - REPLFIELD / GETVALUE"){
    u64 r1 = 0x0123456789ABCDEFull;
    u64 r2 = 0x01234AFFEDEADDEFull;   //in from start(@LSB!) length
    auto tmp = Math::Boolean::REPLFIELD<u64>(r2,r1,12,32);
    REQUIRE( r1 == tmp );
    REQUIRE( r1 != r2 );
    REQUIRE( 0xAFFEDEADull == Math::Boolean::GETVALUE<u64>(r2,12,32) );
    REQUIRE( Math::Boolean::GETVALUE<u64>(r1,44,20) == Math::Boolean::GETVALUE<u64>(r2,44,20) );
  }

  SECTION("6b - SETVALUE / GETVALUE"){
    u64 r1 = 0x0123456789ABCDEFull;
    u64 r2 = 0x01234AFFEDEADDEFull;
    auto tmp = Math::Boolean::SETVALUE<u64>(r2,Math::Boolean::GETVALUE<u64>(r1,12,32),12,32);
    REQUIRE( r1 == tmp );
    REQUIRE( r1 == r2 );
    REQUIRE( 0xAFFEDEADull != Math::Boolean::GETVALUE<u64>(r2,12,32) );
    REQUIRE( Math::Boolean::GETVALUE<u64>(r1,44,20) == Math::Boolean::GETVALUE<u64>(r2,44,20) );
    REQUIRE( Math::Boolean::GETVALUE<u64>(r1,12,32) == Math::Boolean::GETVALUE<u64>(r2,12,32) );
  }

  SECTION("7 - ZQ / INTABS - 1/2"){
    //u64 uref = 1;
    s64 sref = 1;
    for(s64 ii=-1; ii>-1000000; --ii){
      REQUIRE( sref++ == s64(Math::Boolean::ZQ<u64>(u64(ii))) );
      //REQUIRE( uref++ == Math::Boolean::INTABS<s64>(ii) );
    }
  }

  SECTION("7 - ZQ / INTABS - 2/2"){
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

  SECTION("8 - multiply_low_part / multiply_high_part"){
    auto const ii = u32(GENERATE(take(100, random(0, s32(Math::Boolean::__MAX<u16>())))));
    auto const ij = u32(GENERATE(take(100, random(0, s32(Math::Boolean::__MAX<u16>())))));
    CAPTURE(ii);
    CAPTURE(ij);

    u32 ref = ii*ij;
    CAPTURE(ref);

    REQUIRE( u16(ref)     == Math::Discrete::multiply_low_part<u16>(u16(ii),u16(ij)) );
    REQUIRE( u16(ref>>16) == Math::Discrete::multiply_high_part<u16>(u16(ii),u16(ij)) );
  }

  SECTION("9 - midsquare_64"){
    u8 collect = 0;
    for(u16 ii=0; ii<256; ++ii){
      collect |= u8(Math::Hashing::midsquare_64<u16>(ii,8));
    }
    REQUIRE( Math::Boolean::GETFULLMASK<u8>(8) == collect );
  }

  SECTION("10 - GETMAXBITS"){
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

  SECTION("11 - BITSPACE"){
    u64 ref = 1;
    for(u8 ii=0; ii<32; ++ii){
      REQUIRE( ref==Math::Boolean::BITSPACE<u64>(ii) );
      ref <<= 1;
    }
  }

  SECTION("12 - MASK_MSB"){
    u64 ref = 1;
    for(u8 ii=1; ii<64; ++ii){
      REQUIRE( ref==Math::Boolean::MASK_MSB<u64>(ii) );
      ref <<= 1;
    }
  }
}
