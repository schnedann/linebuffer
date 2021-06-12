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

#include "catch.hpp"
#include "bitreverse.h"
#include "math_discrete.h"
#include "Stringhelper.h"

TEST_CASE("Bitreverse"){

  SECTION("simple_method"){
    constexpr static auto const tbits = Math::Boolean::GETBITSOFTYPE<u32>();
    auto const bits = u8(GENERATE(take(10, random(4, 32))));
    auto const mask = Math::Boolean::GETFULLMASK<u32>(bits);
    auto const orig = Math::Boolean::MASKBITS<u32>(u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>())))),mask);
    auto bitrev  = Algorithms::Bitreverse::simple_method<u32>(orig,bits);
    auto revorig = Algorithms::Bitreverse::simple_method<u32>(bitrev,bits);
    CAPTURE(bits);
    CAPTURE(PRNBINVAR(mask,tbits));
    CAPTURE(PRNBINVAR(orig,tbits));
    CAPTURE(PRNBINVAR(bitrev,tbits));
    CAPTURE(PRNBINVAR(revorig,tbits));
    REQUIRE( orig == revorig );
  }

  SECTION("maskshift_method"){
    constexpr static auto const tbits = Math::Boolean::GETBITSOFTYPE<u32>();
    auto const bits = u8(GENERATE(take(10, random(4, 32))));
    auto const mask = Math::Boolean::GETFULLMASK<u32>(bits);
    auto const orig = Math::Boolean::MASKBITS<u32>(u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>())))),mask);
    auto bitrev  = Algorithms::Bitreverse::maskshift_method<u32>(orig,bits);
    auto revorig = Algorithms::Bitreverse::maskshift_method<u32>(bitrev,bits);
    CAPTURE(bits);
    CAPTURE(PRNBINVAR(mask,tbits));
    CAPTURE(PRNBINVAR(orig,tbits));
    CAPTURE(PRNBINVAR(bitrev,tbits));
    CAPTURE(PRNBINVAR(revorig,tbits));
    REQUIRE( orig == revorig );
  }

  SECTION("maskshift_methodV2")  {
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::maskshift_methodV2<u32>(orig,32);
    auto revorig = Algorithms::Bitreverse::maskshift_methodV2<u32>(bitrev,32);
    CAPTURE(PRNBINVAR(orig,32));
    CAPTURE(PRNBINVAR(bitrev,32));
    CAPTURE(PRNBINVAR(revorig,32));
    REQUIRE( orig == revorig );
  }

  SECTION("numerical method - Debug"){
    std::array<u8,16> const ref={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};
    constexpr static u8 const bits = 4;

    for(u8 ii=0; ii<16; ++ii){
      auto bitrev  = Algorithms::Bitreverse::numerical_method<u8>(ii,bits);
      CAPTURE(u16(ii));
      REQUIRE(ref[ii]==bitrev);
    }
  }

  SECTION("numerical method"){
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    constexpr static auto const tbits = Math::Boolean::GETBITSOFTYPE<u32>();
    auto bitrev  = Algorithms::Bitreverse::numerical_method<u32>(orig,tbits);
    auto revorig = Algorithms::Bitreverse::numerical_method<u32>(bitrev,tbits);
    CAPTURE(PRNBINVAR(orig,32));
    CAPTURE(PRNBINVAR(bitrev,32));
    CAPTURE(PRNBINVAR(revorig,32));
    REQUIRE( orig == revorig );
  }

  //--- nibble based methods

  SECTION("nibbleLut_method"){
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::nibbleLut_method<u32>(orig);
    auto revorig = Algorithms::Bitreverse::nibbleLut_method<u32>(bitrev);
    CAPTURE(PRNBINVAR(orig,32));
    CAPTURE(PRNBINVAR(bitrev,32));
    CAPTURE(PRNBINVAR(revorig,32));
    REQUIRE( orig == revorig );
  }

  SECTION("nibbleLut_methodV2"){
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::nibbleLut_methodV2<u32>(orig);
    auto revorig = Algorithms::Bitreverse::nibbleLut_methodV2<u32>(bitrev);
    CAPTURE(PRNBINVAR(orig,32));
    CAPTURE(PRNBINVAR(bitrev,32));
    CAPTURE(PRNBINVAR(revorig,32));
    REQUIRE( orig == revorig );
  }

  //--- Compare results of all methods at same input

  SECTION("Mixed up")  {
    //constexpr static auto const tbits = Math::Boolean::GETBITSOFTYPE<u32>();
    auto const bits = u8(GENERATE(take(10, random(4, 32))));
    auto const mask = Math::Boolean::GETFULLMASK<u32>(bits);
    auto const orig = Math::Boolean::MASKBITS<u32>(u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>())))),mask);
    auto const nibbles = Math::Boolean::BITS2NIBBLES<u8>(bits);


    auto bitrev0 = Algorithms::Bitreverse::simple_method<u32>(orig,bits);
    auto bitrev1 = Algorithms::Bitreverse::nibbleLut_method<u32>(orig,nibbles);
    auto bitrev2 = Algorithms::Bitreverse::nibbleLut_methodV2<u32>(orig,nibbles);
    auto bitrev3 = Algorithms::Bitreverse::maskshift_method<u32>(orig,bits);
    auto bitrev4 = Algorithms::Bitreverse::maskshift_methodV2<u32>(orig,bits);
    auto bitrev5 = Algorithms::Bitreverse::numerical_method<u32>(orig,bits);


    bool use_nibble_algos = 0==(bits%4);
    CAPTURE(use_nibble_algos);
    CAPTURE(u16(bits));
    CAPTURE(PRNBINVAR(mask,32));
    CAPTURE(PRNBINVAR(orig,32));

    if(use_nibble_algos){
      REQUIRE( bitrev0 == bitrev1 );
      REQUIRE( bitrev1 == bitrev2 );
      REQUIRE( bitrev2 == bitrev3 );
      REQUIRE( bitrev3 == bitrev4 );
      REQUIRE( bitrev4 == bitrev5 );
      REQUIRE( bitrev5 == bitrev0 );
    }else{
      REQUIRE( bitrev0 == bitrev3 );
      REQUIRE( bitrev3 == bitrev4 );
      REQUIRE( bitrev4 == bitrev5 );
      REQUIRE( bitrev5 == bitrev0 );
    }
  }
}
