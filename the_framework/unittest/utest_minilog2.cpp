#include "catch.hpp"

#include "dtypes.h"
#include "bitmacros.h"

#include "minilog2.h"

TEST_CASE("Algorithms::Log2::minilog2"){

  SECTION("Algorithms::Log2::minilog2"){
    for(u16 ii=0; ii<u16(256); ++ii){
      auto dut = Algorithms::Log2::minilog2(ii);
      CAPTURE(ii);

      u8 ref = 0;
      u8 mask = Math::Boolean::MASK_MSB<u8>();
      if((ii>0) && (ii>=mask)){
        ref = 7;
      }else{
      mask = Math::Boolean::ARITHSHR<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 6;
      }else{
      mask = Math::Boolean::ARITHSHR<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 5;
      }else{
      mask = Math::Boolean::ARITHSHR<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 4;
      }else{
      mask = Math::Boolean::ARITHSHR<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 3;
      }else{
      mask = Math::Boolean::ARITHSHR<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 2;
      }else{
      mask = Math::Boolean::ARITHSHR<u8>(mask,1);
      if((ii>0) && (ii>=mask)){
        ref = 1;
      }}}}}}}

      REQUIRE(ref == dut);
    }
  }

}
