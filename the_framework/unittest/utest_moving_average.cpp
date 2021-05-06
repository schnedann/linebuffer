#include "catch.hpp"

#include "dtypes.h"
#include "moving_average.h"
#include "bitmacros.h"

TEST_CASE("Algorithms::moving_average"){

  SECTION("Algorithms::moving_average"){
    constexpr size_t const depth = 3;
    constexpr u32 const max = 65536;
    Algorithms::moving_average<u16,depth> movavg;

    u16 ref_c = 0;

    for(u32 ii=1; ii<max; ++ii){
      CAPTURE(ii);

      ref_c = ref_c + ((ii - ref_c)>>1);

      movavg.put(ii);

      CAPTURE(movavg.buffer());
      REQUIRE( (ii-1) ==  movavg.get_s() );
      //REQUIRE( ref_c  ==  movavg.get_c() );
    }
  }

} //TestCase
