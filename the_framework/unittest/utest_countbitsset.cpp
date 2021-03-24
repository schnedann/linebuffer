/*
 * Copyright 2017-2019,Danny Schneider
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

#include "catch.hpp"

#include "dtypes.h"
#include "countbitsset.h"

TEST_CASE("Count-Bits_Set - Brute Force Test"){
  SECTION("Algo 0 - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel<testtype>(ii)));
      }
    }
  }
  SECTION("Algo 0 - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel<testtype>(ii)));
      }
    }
  }

  /*SECTION("Algo 0 - U16"){
    {
      using testtype = u32;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel<testtype>(ii)));
      }
    }
  }*/

  //-----

  SECTION("Algo nibble_lut - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut<testtype>(ii)));
      }
    }
  }
  SECTION("Algo nibble_lut - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut<testtype>(ii)));
      }
    }
  }

  //-----

  SECTION("Algo nibble_lut2 - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut2<testtype>(ii)));
      }
    }
  }
  SECTION("Algo nibble_lut2 - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut2<testtype>(ii)));
      }
    }
  }

  //-----

  SECTION("Algo nibble_lut_ur - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut_ur<testtype>(ii)));
      }
    }
  }
  SECTION("Algo nibble_lut_ur - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut_ur<testtype>(ii)));
      }
    }
  }

  //-----

  SECTION("Algo nibble_lut_ur2 - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut_ur2<testtype>(ii)));
      }
    }
  }
  SECTION("Algo nibble_lut_ur2 - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::nibble_lut_ur2<testtype>(ii)));
      }
    }
  }

  //-----

  SECTION("Algo parallel - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel<testtype>(ii)));
      }
    }
  }
  SECTION("Algo parallel - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel<testtype>(ii)));
      }
    }
  }

  //-----

  SECTION("Algo parallel_2 - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel_2<testtype>(ii)));
      }
    }
  }
  SECTION("Algo parallel_2 - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel_2<testtype>(ii)));
      }
    }
  }

  //-----

  SECTION("Algo parallel_3 - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel_3<testtype>(ii)));
      }
    }
  }
  SECTION("Algo parallel_3 - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::parallel_3<testtype>(ii)));
      }
    }
  }

  //-----

  SECTION("Algo intrinsic_popcnt - U8"){
    {
      using testtype = u8;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::intrinsic_popcnt<testtype>(ii)));
      }
    }
  }
  SECTION("Algo intrinsic_popcnt - U16"){
    {
      using testtype = u16;
      for(testtype ii=0; ii<Math::Boolean::GETFULLMASK<u32>(Math::Boolean::GETBITSOFTYPE<testtype>()); ++ii) {
        testtype ref = Algorithms::CountBitsset::wegner_method<testtype>(ii);
        REQUIRE( u16(ref) == u16(Algorithms::CountBitsset::intrinsic_popcnt<testtype>(ii)));
      }
    }
  }

  //-----
}

/*
TEST_CASE("Count-Bits_Set - Quick Test"){
  SECTION(""){

  }
}*/

TEST_CASE("Count-Bits_Set - Quick Test"){
  SECTION("wegner_method 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::wegner_method<testtype>(mask)));
    }
  }
  SECTION("wegner_method 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::wegner_method<testtype>(mask)));
    }
  }

  SECTION("parallel 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::parallel<testtype>(mask)));
    }
  }
  SECTION("parallel 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::parallel<testtype>(mask)));
    }
  }

  SECTION("parallel_2 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::parallel_2<testtype>(mask)));
    }
  }
  SECTION("parallel_2 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::parallel_2<testtype>(mask)));
    }
  }

  SECTION("parallel_3 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::parallel_3<testtype>(mask)));
    }
  }
  SECTION("parallel_3 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::parallel_3<testtype>(mask)));
    }
  }

  SECTION("nibble_lut_ur 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut_ur<testtype>(mask)));
    }
  }
  SECTION("nibble_lut_ur 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut_ur<testtype>(mask)));
    }
  }

  SECTION("nibble_lut_ur2 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut_ur2<testtype>(mask)));
    }
  }
  SECTION("nibble_lut_ur2 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut_ur2<testtype>(mask)));
    }
  }

  SECTION("nibble_lut 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut<testtype>(mask)));
    }
  }
  SECTION("nibble_lut 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut<testtype>(mask)));
    }
  }

  SECTION("nibble_lut2 64"){
    using testtype = u64;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut2<testtype>(mask)));
    }
  }
  SECTION("nibble_lut2 32"){
    using testtype = u32;
    for(u8 ii=0; ii<Math::Boolean::GETBITSOFTYPE<testtype>(); ++ii) {
      u8 bits = ii+1;
      testtype mask = Math::Boolean::GETFULLMASK<testtype>(bits);
      CAPTURE(u16(bits));
      CAPTURE(mask);
      REQUIRE(u16(bits) == u16(Algorithms::CountBitsset::nibble_lut2<testtype>(mask)));
    }
  }
}
