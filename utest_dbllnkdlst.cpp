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
      REQUIRE(ii == Datastructures::count(dll));
      dll.push_front(ii);
    }
    REQUIRE(elements == Datastructures::count(dll));
  }

  SECTION("2"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      CAPTURE(ii);
      REQUIRE(ii == Datastructures::count(dll));
      dll.push_back(ii);
    }
    REQUIRE(elements == Datastructures::count(dll));
  }

  SECTION("3"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      dll.push_front(ii);
    }

    for(u16 ii=0; ii<elements; ++ii){
      auto tmp = dll.pop_back();
      //CAPTURE(ii);
      REQUIRE(ii == *tmp);
    }
    REQUIRE(0 == Datastructures::count(dll));
  }

  SECTION("4"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      dll.push_back(ii);
    }

    for(u16 ii=0; ii<elements; ++ii){
      auto tmp = dll.pop_front();
      //CAPTURE(ii);
      REQUIRE(ii == *tmp);
    }
    REQUIRE(0 == Datastructures::count(dll));
  }

  SECTION("5"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      dll.push_back(ii);
    }

    u16 ref = 0;
    auto ptr = dll.get_next(nullptr);
    while(Core::Container::is_valid(ptr)){
      CAPTURE(ptr);
      REQUIRE(ref == *(ptr->data.get()));
      ++ref;
      ptr = dll.get_next(ptr);
    }
  }

  SECTION("6"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      dll.push_front(ii);
    }

    u16 ref = 0;
    auto ptr = dll.get_prev(nullptr);
    while(Core::Container::is_valid(ptr)){
      CAPTURE(ptr);
      REQUIRE(ref == *(ptr->data.get()));
      ++ref;
      ptr = dll.get_prev(ptr);
    }
  }

  SECTION("6"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    for(u16 ii=0; ii<elements; ++ii){
      dll.push_front(ii);
      CAPTURE(ii);
      REQUIRE(!has_error(Datastructures::at<u16>(dll,ii)));
      //REQUIRE(ii == *get_data(Datastructures::at<u16>(dll,ii)));
    }
  }

  SECTION("7"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    constexpr u16 const offset   = 2;
    for(u16 ii=0; ii<offset; ++ii){
      dll.push_back(ii);
    }
    for(u16 ii=offset; ii<elements; ++ii){
      dll.push_back(ii);
      auto found = Datastructures::find_match<u16>(dll,[&ii](u16 const& _d)->bool{
        return ((ii-1)==_d);
      });
      CAPTURE(ii);
      REQUIRE( !found.first );
      REQUIRE( (ii-1) == found.second );
    }
  }

  SECTION("8"){
    Datastructures::dbllnkdlst<u16> dll;

    constexpr u16 const elements = 10000;
    constexpr u16 const offset   = 2;
    for(u16 ii=0; ii<offset; ++ii){
      dll.push_back(ii);
    }
    for(u16 ii=offset; ii<elements; ++ii){
      dll.push_back(ii);
      auto found = Datastructures::rfind_match<u16>(dll,[&ii](u16 const& _d)->bool{
        return ((ii-1)==_d);
      });
      CAPTURE(ii);
      REQUIRE( !found.first );
      REQUIRE( (ii-1) == found.second );
    }
  }

}
