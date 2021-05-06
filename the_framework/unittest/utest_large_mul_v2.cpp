#include <iostream>
#include <string>

#include "catch.hpp"

#include "dtypes.h"
#include "math_discrete.h"
#include "large_mul_v2.h"

using namespace std;

TEST_CASE("Math::Large_Mul_V2"){

  SECTION("1 - u16*u16=u32"){
    using full_t = u32;
    using half_t = u16;

    auto const a = half_t(GENERATE(take(75, random(0, 65535))));
    auto const b = half_t(GENERATE(take(75, random(0, 65535))));

    auto dut = Math::Large_Mul::mply<half_t,full_t>(a,b);

    full_t ref = Math::Boolean::ARITHSHL<full_t>(Math::Discrete::multiply_high_part<half_t>(a,b),Math::Boolean::GETBITSOFTYPE<half_t>());
    //CAPTURE(ref);
    ref = Math::Boolean::OR<full_t>(ref,Math::Discrete::multiply_low_part<half_t>(a,b));

    CAPTURE(a);
    CAPTURE(b);
    REQUIRE(dut == ref);
  }

  SECTION("2 - u32*u32=u64"){
    using full_t = u64;
    using half_t = u32;

    auto const a = half_t(GENERATE(take(75, random(Math::Boolean::__MIN_SIGNED<s32>(), Math::Boolean::__MAX_SIGNED<s32>()))));
    auto const b = half_t(GENERATE(take(75, random(Math::Boolean::__MIN_SIGNED<s32>(), Math::Boolean::__MAX_SIGNED<s32>()))));

    auto dut = Math::Large_Mul::mply<half_t,full_t>(a,b);

    full_t ref = Math::Boolean::ARITHSHL<full_t>(Math::Discrete::multiply_high_part<half_t>(a,b),Math::Boolean::GETBITSOFTYPE<half_t>());
    //CAPTURE(ref);
    ref = Math::Boolean::OR<full_t>(ref,Math::Discrete::multiply_low_part<half_t>(a,b));

    CAPTURE(a);
    CAPTURE(b);
    REQUIRE(dut == ref);
  }

  SECTION("3 - "){
    for(u16 ii=1; ii<256; ++ii){
      for(u16 ij=1; ij<256; ++ij){
        CAPTURE(u16(ii));
        CAPTURE(u16(ij));
        REQUIRE( (ii*ij) == Math::Large_Mul::mply<u8,u16>(ii,ij) );
      }
    }
  }
}
