#include <iostream>
#include <iomanip>
#include <cmath>

#include "catch.hpp"

#include "dtypes.h"
#include "ovf_save.h"
#include "log2.h"

using namespace std;

TEST_CASE( "Math::OverflowSafe", "[math]" ){

  SECTION( "Math::OverflowSafe::add<u8>" ){
    u8 res;
    REQUIRE( true == Math::OverflowSafe::add<u8>(255,255,res) );
    REQUIRE( 254 == res);

    REQUIRE( false == Math::OverflowSafe::add<u8>(254,1,res) );
    REQUIRE( 255 == res);
  }

  SECTION( "Math::OverflowSafe::sub<u8>" ){
    u8 res;
    REQUIRE( true == Math::OverflowSafe::sub<u8>(254,255,res) );
    REQUIRE( 255 == res);

    REQUIRE( false == Math::OverflowSafe::sub<u8>(254,253,res) );
    REQUIRE( 1 == res);
  }

  SECTION( "Math::OverflowSafe::add<u8> 2/2" ){
    INFO( "Xref Test ADD --> Math::OverflowSafe::add<u8>" );
    u8 res;
    for(u16 ii=0; ii<256; ++ii){
      for(u16 ij=0; ij<256; ++ij){
        bool ovf_expected = ((ii+ij)>255)?(true):(false);
        auto ovf = Math::OverflowSafe::add<u8>(static_cast<u8>(ii),static_cast<u8>(ij),res);
        CAPTURE(  ii );
        CAPTURE(  ij );
        CAPTURE( ovf_expected );
        CAPTURE( u16(res) );
        REQUIRE( res == static_cast<u8>(ii+ij));
        REQUIRE( ovf == ovf_expected);
      }
    }
  }

  SECTION( "Math::OverflowSafe::sub<u8> 2/2" ){
    INFO( "Xref Test SUB --> Math::OverflowSafe::ovf_save" );
    u8 res;
    for(s16 ii=0; ii<256; ++ii){
      for(s16 ij=0; ij<256; ++ij){
        bool ovf_expected = ((ii-ij)<0)?(true):(false);
        auto ovf = Math::OverflowSafe::sub<u8>(static_cast<u8>(ii),static_cast<u8>(ij),res);
        CAPTURE(  ii );
        CAPTURE(  ij );
        CAPTURE( ovf_expected );
        CAPTURE( u16(res) );
        REQUIRE( res == static_cast<u8>(ii-ij));
        REQUIRE( ovf == ovf_expected);
      }
    }
  }

  SECTION( "mul2" ){
    INFO( "Xref Test MUL --> Math::OverflowSafe::ovf_save" );
    u8 res;
    for(s16 ii=0; ii<256; ++ii){
      for(s16 ij=1; ij<256; ++ij){
        CAPTURE(  ii );
        CAPTURE(  ij );
        auto const a = Math::Log2::log2<u8>(static_cast<u8>(ii));
        auto const b = Math::Log2::log2<u8>(static_cast<u8>(ij));
        CAPTURE( a );
        CAPTURE( b );
        bool ovf_expected = ((a+b)>8)?(true):(false);
        auto ovf = Math::OverflowSafe::mul<u8>(static_cast<u8>(ii),static_cast<u8>(ij),res);
        CAPTURE( ovf_expected );
        CAPTURE( u16(res) );
        REQUIRE( res == static_cast<u8>(ii*ij));
        REQUIRE( ovf == ovf_expected);
      }
    }
  }

  SECTION( "div2" ){
    INFO( "Xref Test DIV --> Math::OverflowSafe::ovf_save" );
    u8 res;
    for(s16 ii=0; ii<255; ++ii){
      for(s16 ij=1; ij<255; ++ij){
        //bool ovf_expected = false;
        Math::OverflowSafe::div<u8>(static_cast<u8>(ii),static_cast<u8>(ij),res);
        CAPTURE(  ii );
        CAPTURE(  ij );
        //CAPTURE( ovf_expected );
        CAPTURE( u16(res) );
        REQUIRE( res == static_cast<u8>(ii/ij));
        //REQUIRE( ovf == ovf_expected);
      }
    }
  }

  //--------------------------------------------------

  SECTION( "Math::OverflowSafe::comp_int" ){
    for(s16 ii=0; ii<255; ++ii){
      for(s16 ij=1; ij<255; ++ij){
        if(ii<ij){
          REQUIRE( -1 == Math::OverflowSafe::comp_int<s8>(static_cast<s8>(ii),static_cast<s8>(ij)) );
        }else if(ii>ij){
          REQUIRE( 1 == Math::OverflowSafe::comp_int<s8>(static_cast<s8>(ii),static_cast<s8>(ij)) );
        }else{
          REQUIRE( 0 == Math::OverflowSafe::comp_int<s8>(static_cast<s8>(ii),static_cast<s8>(ij)) );
        }
      }
    }
  }

  //--------------------------------------------------

  SECTION( "Math::OverflowSafe::satt_sadd" ){
    s8 _c = -128;
    for(u16 ii=0; ii<1000; ++ii){
      _c = Math::OverflowSafe::satt_sadd<s8>(_c,1);

      s16 ref = -128 + static_cast<s16>(ii);

      if(ii<256){
        REQUIRE( static_cast<s16>(_c) == ref );
      }else{
        REQUIRE( static_cast<s16>(_c) == static_cast<s16>(127) );
      }
    }
  }

  SECTION( "Math::OverflowSafe::satt_ssub" ){

  }

  SECTION( "Math::OverflowSafe::satt_uadd" ){
    u8 _c = 0;
    for(u16 ii=0; ii<1000; ++ii){
      _c = Math::OverflowSafe::satt_uadd<u8>(_c,1);

      u16 ref = static_cast<u16>(ii);

      if(ii<256){
        REQUIRE( static_cast<u16>(_c) == ref );
      }else{
        REQUIRE( static_cast<u16>(_c) == static_cast<u16>(255) );
      }
    }
  }

  SECTION( "Math::OverflowSafe::satt_usub" ){

  }

  //--------------------------------------------------

  SECTION( "Math::OverflowSafe::add_of" ){

  }

  SECTION( "Math::OverflowSafe::sub_of" ){

  }

  //--------------------------------------------------
}
