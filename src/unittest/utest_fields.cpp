#include <iostream>
#include <string>

#include "catch.hpp"

#include "dtypes.h"
#include "fields.h"

using namespace std;

TEST_CASE("fields"){
  SECTION("1"){
    auto fse = Datastructures::make_field_se<u16>(0,8);
    auto fsl = Datastructures::make_field_sl<u16>(fse);
    auto ffl = Datastructures::make_field_fl<u16>(fsl);

    REQUIRE( 0 == fse.start );
    REQUIRE( 8 == fse.end );
    REQUIRE( 0 == fsl.start );
    REQUIRE( 8 == fsl.length );
    REQUIRE( 0 == ffl.first );
    REQUIRE( 7 == ffl.last );

    REQUIRE( 3 == Datastructures::middle_field<u16>(fse) );
  }

  SECTION("2"){
    auto fsl = Datastructures::make_field_sl<u16>(0,8);
    auto ffl = Datastructures::make_field_fl<u16>(fsl);
    auto fse = Datastructures::make_field_se<u16>(ffl);

    REQUIRE( 0 == fse.start );
    REQUIRE( 8 == fse.end );
    REQUIRE( 0 == fsl.start );
    REQUIRE( 8 == fsl.length );
    REQUIRE( 0 == ffl.first );
    REQUIRE( 7 == ffl.last );

    REQUIRE( 3 == Datastructures::middle_field(fsl) );
  }

  SECTION("3"){
    auto ffl = Datastructures::make_field_fl<u16>(0,7);
    auto fse = Datastructures::make_field_se<u16>(ffl);
    auto fsl = Datastructures::make_field_sl<u16>(fse);

    REQUIRE( 0 == fse.start );
    REQUIRE( 8 == fse.end );
    REQUIRE( 0 == fsl.start );
    REQUIRE( 8 == fsl.length );
    REQUIRE( 0 == ffl.first );
    REQUIRE( 7 == ffl.last );

    REQUIRE( 3 == Datastructures::middle_field(ffl) );
  }

  SECTION("4"){
    auto ffl = Datastructures::make_field_fl<u16>(0,3);
    auto bound = Datastructures::make_field_fl<u16>(1,8);

    for(u16 ii=0; ii<10; ++ii){
      CAPTURE(ii);
      auto tmp = Datastructures::move_field<u16>(ffl,ii);
      if((ii>0) && (ii<6)){
        REQUIRE(  Datastructures::is_in_bounds<u16>(tmp,bound) );
      }else{
        REQUIRE( !Datastructures::is_in_bounds<u16>(tmp,bound) );
      }
    }
  }

  SECTION("5"){
    auto ffl = Datastructures::make_field_se<u16>(0,4);
    auto bound = Datastructures::make_field_se<u16>(1,9);

    for(u16 ii=0; ii<10; ++ii){
      CAPTURE(ii);
      auto tmp = Datastructures::move_field<u16>(ffl,ii);
      if((ii>0) && (ii<6)){
        REQUIRE(  Datastructures::is_in_bounds<u16>(tmp,bound) );
      }else{
        REQUIRE( !Datastructures::is_in_bounds<u16>(tmp,bound) );
      }
    }
  }

  SECTION("6"){
    auto ffl = Datastructures::make_field_sl<u16>(0,4);
    auto bound = Datastructures::make_field_sl<u16>(1,8);

    for(u16 ii=0; ii<10; ++ii){
      CAPTURE(ii);
      auto tmp = Datastructures::move_field<u16>(ffl,ii);
      if((ii>0) && (ii<6)){
        REQUIRE(  Datastructures::is_in_bounds<u16>(tmp,bound) );
      }else{
        REQUIRE( !Datastructures::is_in_bounds<u16>(tmp,bound) );
      }
    }
  }

}
