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

#include <random>
#include <array>
#include <cmath>

#include "catch.hpp"

#include "dtypes.h"
#include "log2.h"
#include "bitmacros.h"
#include "flowpoint_util.h"
#include "Stringhelper.h"

TEST_CASE("Math::Log2 using stdlib as reference"){

  SECTION("ceil_log2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::ceil_log2<u32>(rnd);
    auto ref = static_cast<u32>(ceill(std::log2l(rnd)));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION("floor_log2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::floor_log2<u32>(rnd);
    auto ref = static_cast<u32>(floorl(std::log2l(rnd)));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( u16(ref) == u16(res) );
  }

  //-----

  SECTION("is_power_of_2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::is_power_of_2<u32>(rnd);
    auto ref = Math::Boolean::IS_ONEHOT<u32>(rnd);
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( u16(ref) == u16(res) );
  }

  //-----

  SECTION("ceil_log2_v1"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::ceil_log2_v1<u32>(rnd);
    auto ref = ceill(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION("floor_log2_v1"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::floor_log2_v1<u32>(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  //-----

  SECTION("ceil_log2_v2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::ceil_log2_v2<u32>(rnd);
    auto ref = ceill(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION("floor_log2_v2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::floor_log2_v2<u32>(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION( "ceil_log2_v2 2/2" ) {
    INFO( "Xref Test LOG2 --> Math::OverflowSafe::ovf_save" );
    for(u16 ii=0; ii<Math::Boolean::GETFULLMASK<u16>(Math::Boolean::GETBITSOFTYPE<u8>()); ++ii){
      u8 res = Math::Log2::ceil_log2_v2<u8>(static_cast<u8>(ii));
      CAPTURE(  ii );
      CAPTURE( u16(res) );
      double dbl = std::ceil(std::log2(ii));
      CAPTURE( dbl );
      REQUIRE( res == static_cast<u8>(dbl) );
    }
  }

  SECTION( "floor_log2_v2 2/2" ) {
    INFO( "Xref Test LOG2 --> Math::OverflowSafe::ovf_save" );
    for(u16 ii=0; ii<Math::Boolean::GETFULLMASK<u16>(Math::Boolean::GETBITSOFTYPE<u8>()); ++ii){
      u8 res = Math::Log2::floor_log2_v2<u8>(static_cast<u8>(ii));
      CAPTURE(  ii );
      CAPTURE( u16(res) );
      double dbl = std::floor(std::log2(ii));
      CAPTURE( dbl );
      REQUIRE( res == static_cast<u8>(dbl) );
    }
  }

  //-----

  SECTION("floor_log2_v3"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::floor_log2_v3<u32>(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION( "floor_log2_v3 2/2" ) {
    INFO( "Xref Test LOG2 --> Math::OverflowSafe::ovf_save" );
    for(u16 ii=0; ii<Math::Boolean::GETFULLMASK<u16>(Math::Boolean::GETBITSOFTYPE<u8>()); ++ii){
      u8 res = Math::Log2::floor_log2_v3<u8>(static_cast<u8>(ii));
      CAPTURE(  ii );
      CAPTURE( u16(res) );
      double dbl = std::floor(std::log2(ii));
      CAPTURE( dbl );
      REQUIRE( res == static_cast<u8>(dbl) );
    }
  }

  //-----

  SECTION("log2c"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::log2c<u32>(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  //-----

  SECTION("Math::Log2::log2 1/3"){
    std::array<u8,50> res{};
    for(u64 ii=0; ii<res.size(); ++ii){
      res[ii] = u8(Math::Log2::log2<u64>(ii));
    }
    Utility::Strings::print_array<u8>(res.data(),res.size());
  }

  SECTION("Math::Log2::log2 2/3"){
    {
      //Compare log2 from stdlib with own implementation

      /* http://www.cplusplus.com/doc/tutorial/typecasting/
       * If the conversion is from a floating-point type to an integer type,
       * the value is truncated (the decimal part is removed). If the result
       * lies outside the range of representable values by the type,
       * the conversion causes undefined behavior.
       */

      for(u64 ii=1; ii>0; ii<<=1){
        CAPTURE(ii);
        auto res1 = Math::Log2::log2<u64>(ii);
        auto res2 = u64(std::log2(ii));
        REQUIRE(res1==res2);
      }
    }
  }

  SECTION("Math::Log2::log2 3/3"){
//TODO
    /*{
      for(u64 ii=1; ii>0; ii=ii*2+1){
        CAPTURE(ii);
        auto res1 = Math::Log2::log2<u64>(ii);
        double res_i = std::round(std::log2(ii)); //std::round()
        CAPTURE(res_i);
        auto res2 = u64(res_i);
        REQUIRE(res1==res2);
      }
    }*/
  }

  //-----

  SECTION("Math::Log2::floorLog2_16"){
    auto rnd = u16(GENERATE(take(10000, random(s32(0), s32(Math::Boolean::__MAX<u16>())))));
    auto res = Math::Log2::floorLog2_16(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION("Math::Log2::floorLog2_32"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Math::Log2::floorLog2_32(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(PRNBINVAR(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  //-----

}

TEST_CASE("Math::Log2::minilog2"){

  SECTION("Math::Log2::minilog2"){
    for(u16 ii=0; ii<u16(256); ++ii){
      auto dut = Math::Log2::minilog2(ii);
      CAPTURE(ii);

      u8 ref = 0;
      u8 mask = Math::Boolean::MASK_MSB<u8>();
      if((ii>0) && (ii>=mask)){
        ref = 7;
      }else{
      mask = Math::Boolean::Logic_Shift_R<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 6;
      }else{
      mask = Math::Boolean::Logic_Shift_R<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 5;
      }else{
      mask = Math::Boolean::Logic_Shift_R<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 4;
      }else{
      mask = Math::Boolean::Logic_Shift_R<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 3;
      }else{
      mask = Math::Boolean::Logic_Shift_R<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 2;
      }else{
      mask = Math::Boolean::Logic_Shift_R<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 1;
      }}}}}}}

      REQUIRE(ref == dut);
    }
  }

}
