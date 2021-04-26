#include "catch.hpp"

#include "dtypes.h"
#include "fifo_fixed_size.h"
#include "bitmacros.h"

TEST_CASE("Algorithms::fifo_fixed_size"){

  SECTION("Algorithms::fifo_fixed_size"){
    constexpr size_t const depth = 10;
    constexpr u32 const max = 65536;
    Algorithms::fifo_fixed_size<u16,depth> ffs;

    u16 ij = 0;
    for(u32 ii=0; ii<max; ++ii){

      CAPTURE(ii);
      CAPTURE(ij);

      ffs.put(u16(ii));

      CAPTURE(ffs.is_filled());
      CAPTURE(ffs.buffer());

      if(ii<(depth-1)){
        REQUIRE( 0 == ffs.get() );
      }else{
        REQUIRE( ij++ == ffs.get() );
      }
    }
  }

} //TestCase
