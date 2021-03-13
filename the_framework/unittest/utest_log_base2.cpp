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

#include "catch.hpp"

#include "dtypes.h"
#include "log_base2.h"
#include "bitmacros.h"
#include "flowpoint_util.h"
#include "Stringhelper.h"

TEST_CASE("Log2 using stdlib as reference"){

  SECTION("ceil_log2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Algorithms::Log2::ceil_log2<u32>(rnd);
    auto ref = ceill(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(utility::strings::prnbin(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION("floor_log2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Algorithms::Log2::floor_log2<u32>(rnd);
    auto ref = static_cast<u32>(floorl(log2l(rnd)));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(utility::strings::prnbin(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( u16(ref) == u16(res) );
  }

  SECTION("is_power_of_2"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Algorithms::Log2::is_power_of_2<u32>(rnd);
    auto ref = Math::Boolean::IS_ONEHOT<u32>(rnd);
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(utility::strings::prnbin(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( u16(ref) == u16(res) );
  }

  SECTION("ceil_log2_v1"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Algorithms::Log2::ceil_log2_v1<u32>(rnd);
    auto ref = ceill(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(utility::strings::prnbin(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION("floor_log2_v1"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Algorithms::Log2::floor_log2_v1<u32>(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(utility::strings::prnbin(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

  SECTION("log2c"){
    auto rnd = u32(GENERATE(take(10000, random(Math::Boolean::__MIN<s32>(), Math::Boolean::__MAX<s32>()))));
    auto res = Algorithms::Log2::log2c<u32>(rnd);
    auto ref = floorl(log2l(rnd));
    CAPTURE(rnd);
    CAPTURE(res);
    CAPTURE(ref);
    CAPTURE(utility::strings::prnbin(rnd,Math::Boolean::GETBITSOFTYPE<decltype(rnd)>()));
    REQUIRE( Math::Flowpoint::approximatelyEqual<long double>(ref,static_cast<long double>(res),static_cast<long double>(0.5)) );
  }

}

