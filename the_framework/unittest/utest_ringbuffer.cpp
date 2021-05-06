#include "catch.hpp"

#include "dtypes.h"
#include "ringbuffer.h"
#include "bitmacros.h"

TEST_CASE("Datastructures::ringbuffer"){

  SECTION("Datastructures::ringbuffer a"){

    Datastructures::ringbuffer<u16,u8,50> rb;

    u16 ij = 100;
    u16 free = 50;
    for(u16 ii=0; ii<(3*50); ++ii){
      REQUIRE(free == rb.free());
      rb.push(&ii);
      if(ii>=50){
        if(ii<100){
          auto ptr = rb.data();
          for(u16 ik=0; ik < 50; ++ik){
            ptr[ik] += 2;
          }
        }else{
          u16 dut;
          rb.pop(&dut);
          REQUIRE( dut == ij );
          ++ij;
        }
      }else{
        if(free>0){
          --free;
        }
      }
    }
  }

  SECTION("Datastructures::ringbuffer b"){
    Datastructures::ringbuffer<u16,u8,50> rb;

    u16 cnt = 0;
    {
      u16 pushs = 0;
      do{
        rb.pseudopush();
        ++pushs;
        if(0==(cnt%3)){
          rb.undopush();
          --pushs;
        }
        REQUIRE( (50-pushs) == rb.free() );
        ++cnt;
      }while(!rb.full());

      u16 pops = 0;
      while(!rb.empty()){
        rb.undopush();
        ++pops;
        if(0==(cnt%3)){
          rb.pseudopush();
          --pops;
        }
        REQUIRE( pops == rb.free() );
        --cnt;
      }
    }
    REQUIRE(0 == cnt);
  }

} //TestCase
