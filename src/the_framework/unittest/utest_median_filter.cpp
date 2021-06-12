#include "catch.hpp"

#include "dtypes.h"
#include "median_filter.h"
#include "bitmacros.h"

TEST_CASE("Algorithms::median_filter"){

  SECTION("Algorithms::median_filter"){
    auto min = s16(Math::Boolean::__MIN_SIGNED<s8>());
    auto max = s16(Math::Boolean::__MAX_SIGNED<s8>());

    Algorithms::median_filter<s16,2> mf;

    u8 cnt = 0;
    for(s16 ii=min; ii<s16(max+1); ++ii){
      CAPTURE(ii);
      CAPTURE(cnt);

      mf.put(ii);

      CAPTURE(mf.buffer());

      if(cnt<2){
        REQUIRE( 0 == mf.get());
        ++cnt;
      }else if(cnt<3){
        REQUIRE( (ii) == mf.get());
        ++cnt;
      }else if(cnt<4){
        REQUIRE( (ii-1) == mf.get());
        ++cnt;
      }else{
        REQUIRE( (ii-2) == mf.get() );
      }
    }

  }

} //TestCase
