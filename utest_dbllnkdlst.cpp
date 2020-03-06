#include <iostream>
#include <string>

#include "catch.hpp"

#include "dtypes.h"
#include "dbllnkdlst.h"

using namespace std;

TEST_CASE("Datastructures::dbllnkdlst"){

  SECTION("1"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      CAPTURE(ii);
      REQUIRE(ii == dll.count());
      dll.push_front(ii);
    }
    REQUIRE(elements == dll.count());
  }

  SECTION("2"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      CAPTURE(ii);
      REQUIRE(ii == dll.count());
      dll.push_back(ii);
    }
    REQUIRE(elements == dll.count());
  }

  SECTION("3"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      dll.push_front(ii);
    }

    for(u16 ii=0; ii<elements; ++ii){
      auto tmp = dll.pop_back();
      REQUIRE(ii == *tmp);
    }
    REQUIRE(0 == dll.count());
  }

  SECTION("4"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      dll.push_back(ii);
    }

    for(u16 ii=0; ii<elements; ++ii){
      auto tmp = dll.pop_front();
      REQUIRE(ii == *tmp);
    }
    REQUIRE(0 == dll.count());
  }

}
