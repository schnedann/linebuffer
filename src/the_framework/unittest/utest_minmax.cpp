#include "catch.hpp"

#include "dtypes.h"
#include "bitmacros.h"

#include "minmax.h"

TEST_CASE("Algorithms::minmax"){

  SECTION("class minmax"){
    auto min = Math::Boolean::__MIN_SIGNED<s8>();
    auto max = Math::Boolean::__MAX_SIGNED<s8>();

    Algorithms::minmax<s8> mm(max,min);

    for(s16 ii=min; ii<s16(max+1); ++ii){
      mm.put(s8(ii));
    }
    REQUIRE(min==mm.get_min());
    REQUIRE(max==mm.get_max());
  }

} //TestCase
