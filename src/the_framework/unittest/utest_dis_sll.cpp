#include <array>

#include "catch.hpp"

#include "dtypes.h"
#include "dis_sll.h"
#include "bitmacros.h"
#include "iterators.h"

class scope_mon{
private:
  u16 id{0};
  Core::Container::iterator_t<u16> ptr{nullptr};
public:
  scope_mon()=default;
  scope_mon(u16 _id,Core::Container::iterator_t<u16> _ptr):id(_id),ptr(_ptr){};
  ~scope_mon();
};

scope_mon::~scope_mon(){
  *ptr = id;
}

TEST_CASE("Datastructures::dis_sll"){

  SECTION("Datastructures::dis_sll a"){
    Datastructures::dis_sll<u16> dsll;
    constexpr u16 const max = 25000;

    for(u16 ii=0; ii<max; ++ii){
      dsll.add(ii);
    }

    bool trigger = true;
    bool run = true;
    u16 idx = max;
    while(run){
      auto data = dsll.next(trigger);
      trigger = false;

      run = !Core::Flow::has_error(data);
      if(run){
        REQUIRE( (max-idx) == Core::Flow::get_value(data) );
      }else{
        break;
      }
      --idx;
    }
    REQUIRE( 0 == idx );
  }

  SECTION("Datastructures::dis_sll b"){
    Datastructures::dis_sll<scope_mon> dsll;

    constexpr u16 const max = 5000;
    std::array<u16,max> dut{};
    for(u16 ii=0; ii<max; ++ii){
      dsll.add(scope_mon(ii,&dut[ii]));
    }

    u16 ref = 0;
    for(auto const& _x:dut){
      REQUIRE( _x == ref++ );
    }
  }
} //TestCase
