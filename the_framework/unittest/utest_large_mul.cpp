#include <iostream>
#include <string>

#include "catch.hpp"

#include "dtypes.h"
#include "math_discrete.h"
#include "large_mul.h"

using namespace std;

TEST_CASE("Math::Large_Mul"){
  SECTION("1 - u16*u16=u32"){
    auto const a = u16(GENERATE(take(75, random(0, 65535))));
    auto const b = u16(GENERATE(take(75, random(0, 65535))));

    auto dut = Math::Large_Mul::mulu16(a,b);

    u32 ref = Math::Boolean::ARITHSHL<u32>(Math::Discrete::multiply_high_part<u16>(a,b),Math::Boolean::GETBITSOFTYPE<u16>());
    CAPTURE(ref);
        ref = Math::Boolean::OR<u32>(ref,Math::Discrete::multiply_low_part<u16>(a,b));

    CAPTURE(a);
    CAPTURE(b);
    REQUIRE(dut == ref);
  }

  SECTION("2 - u32*u32=u64"){
    auto const a = u32(GENERATE(take(75, random(Math::Boolean::__MIN_SIGNED<s32>(), Math::Boolean::__MAX_SIGNED<s32>()))));
    auto const b = u32(GENERATE(take(75, random(Math::Boolean::__MIN_SIGNED<s32>(), Math::Boolean::__MAX_SIGNED<s32>()))));

    auto dut = Math::Large_Mul::mulu32(a,b);

    u32 ref = Math::Boolean::ARITHSHL<u64>(Math::Discrete::multiply_high_part<u32>(a,b),Math::Boolean::GETBITSOFTYPE<u32>());
    CAPTURE(ref);
        ref = Math::Boolean::OR<u64>(ref,Math::Discrete::multiply_low_part<u32>(a,b));

    CAPTURE(a);
    CAPTURE(b);
    REQUIRE(dut == ref);
  }
}
