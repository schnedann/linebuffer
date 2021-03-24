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

  SECTION("simple_method")  {
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::simple_method<u32>(orig);
    auto revorig = Algorithms::Bitreverse::simple_method<u32>(bitrev);
    CAPTURE(utility::strings::prnbin(orig,32));
    CAPTURE(utility::strings::prnbin(bitrev,32));
    CAPTURE(utility::strings::prnbin(revorig,32));
    REQUIRE( orig == revorig );
  }

  SECTION("nibbleLut_method")  {
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::nibbleLut_method<u32>(orig);
    auto revorig = Algorithms::Bitreverse::nibbleLut_method<u32>(bitrev);
    CAPTURE(utility::strings::prnbin(orig,32));
    CAPTURE(utility::strings::prnbin(bitrev,32));
    CAPTURE(utility::strings::prnbin(revorig,32));
    REQUIRE( orig == revorig );
  }

  SECTION("nibbleLut_methodV2")  {
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::nibbleLut_methodV2<u32>(orig);
    auto revorig = Algorithms::Bitreverse::nibbleLut_methodV2<u32>(bitrev);
    CAPTURE(utility::strings::prnbin(orig,32));
    CAPTURE(utility::strings::prnbin(bitrev,32));
    CAPTURE(utility::strings::prnbin(revorig,32));
    REQUIRE( orig == revorig );
  }

  SECTION("maskshift_method")  {
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::maskshift_method<u32>(orig,32);
    auto revorig = Algorithms::Bitreverse::maskshift_method<u32>(bitrev,32);
    CAPTURE(utility::strings::prnbin(orig,32));
    CAPTURE(utility::strings::prnbin(bitrev,32));
    CAPTURE(utility::strings::prnbin(revorig,32));
    REQUIRE( orig == revorig );
  }

  SECTION("maskshift_methodV2")  {
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto bitrev  = Algorithms::Bitreverse::maskshift_methodV2<u32>(orig,32);
    auto revorig = Algorithms::Bitreverse::maskshift_methodV2<u32>(bitrev,32);
    CAPTURE(utility::strings::prnbin(orig,32));
    CAPTURE(utility::strings::prnbin(bitrev,32));
    CAPTURE(utility::strings::prnbin(revorig,32));
    REQUIRE( orig == revorig );
  }

  SECTION("Mixed up")  {
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));

    auto bitrev0 = Algorithms::Bitreverse::simple_method<u32>(orig);
    auto bitrev1 = Algorithms::Bitreverse::nibbleLut_method<u32>(orig);
    auto bitrev2 = Algorithms::Bitreverse::nibbleLut_methodV2<u32>(orig);
    auto bitrev3 = Algorithms::Bitreverse::maskshift_method<u32>(orig,32);
    auto bitrev4 = Algorithms::Bitreverse::maskshift_methodV2<u32>(orig,32);

    REQUIRE( bitrev0 == bitrev1 );
    REQUIRE( bitrev1 == bitrev2 );
    REQUIRE( bitrev2 == bitrev3 );
    REQUIRE( bitrev3 == bitrev4 );
    REQUIRE( bitrev4 == bitrev0 );
  }

  SECTION("numerical method - Debug"){
    std::array<u8,16> ref={0,8,4,12,2,10,6,14,1,9,5,13,3,11,7,15};

    for(u8 ii=0; ii<16; ++ii){
      auto bitrev  = Algorithms::Bitreverse::numerical_method<u8,4>(ii);
      CAPTURE(u16(ii));
      REQUIRE(ref[ii]==bitrev);
    }
  }

  SECTION("numerical method"){
    auto const orig = u32(GENERATE(take(5000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    constexpr auto const tbits = Math::Boolean::GETBITSOFTYPE<u32>();
    auto bitrev  = Algorithms::Bitreverse::numerical_method<u32,tbits>(orig);
    auto revorig = Algorithms::Bitreverse::numerical_method<u32,tbits>(bitrev);
    CAPTURE(utility::strings::prnbin(orig,32));
    CAPTURE(utility::strings::prnbin(bitrev,32));
    CAPTURE(utility::strings::prnbin(revorig,32));
    REQUIRE( orig == revorig );
  }
}
