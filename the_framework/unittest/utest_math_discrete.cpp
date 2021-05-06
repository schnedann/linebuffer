/****************************************
 * Includes
 ****************************************/
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>

#include "catch.hpp"

#include "dtypes.h"
#include "math_discrete.h"
#include "Stringhelper.h"

/****************************************
 * Defines
 ****************************************/



/****************************************
 * Namespaces
 ****************************************/

using namespace std;

/****************************************
 * local Prototypes
 ****************************************/



/****************************************
 * Global Constants
 ****************************************/



/****************************************
 * Typedefs
 ****************************************/



//--- Code

TEST_CASE("Math::Averaging","[math discrete]"){

  SECTION("Math::Averaging::median_of_three"){
    REQUIRE( 2 == Math::Averaging::median_of_three(1,2,3));
    REQUIRE( 2 == Math::Averaging::median_of_three(2,3,1));
    REQUIRE( 2 == Math::Averaging::median_of_three(3,1,2));

    REQUIRE( 2 == Math::Averaging::median_of_three(1,3,2));
    REQUIRE( 2 == Math::Averaging::median_of_three(3,2,1));
    REQUIRE( 2 == Math::Averaging::median_of_three(2,1,3));

    REQUIRE( 2 == Math::Averaging::median_of_three(2,1,3));
    REQUIRE( 2 == Math::Averaging::median_of_three(1,3,2));
    REQUIRE( 2 == Math::Averaging::median_of_three(3,2,1));
  }
}

TEST_CASE("Math::Discrete","[math discrete]"){

  SECTION("Math::Discrete::multiply_low_part"){
    auto const a = u16(GENERATE(take(75, random(0, 65535))));
    auto const b = u16(GENERATE(take(75, random(0, 65535))));
    u32 const c = u32(a)*u32(b);
    CAPTURE(a);
    CAPTURE(b);
    CAPTURE(c);
    REQUIRE( u16(c) == Math::Discrete::multiply_low_part<u16>(a,b) );
  }

  SECTION("Math::Discrete::multiply_high_part"){
    auto const a = u16(GENERATE(take(75, random(0, 65535))));
    auto const b = u16(GENERATE(take(75, random(0, 65535))));
    u32 const c = u32(a)*u32(b);
    CAPTURE(a);
    CAPTURE(b);
    CAPTURE(c);
    REQUIRE( u16(c>>16) == Math::Discrete::multiply_high_part<u16>(a,b) );
  }

  SECTION("14 - multiply_low_part / multiply_high_part"){
    for(u16 ii=0; ii<256; ++ii){
      for(u16 ij=0; ij<256; ++ij){
        u16 ref = ii*ij;
        REQUIRE( u8(ref)    == Math::Discrete::multiply_low_part<u8>(u8(ii),u8(ij)) );
        REQUIRE( u8(ref>>8) == Math::Discrete::multiply_high_part<u8>(u8(ii),u8(ij)) );
      }
    }
  }

  SECTION("Math::nextpow2"){
    u32 nextpower = 1;
    for(u32 ii=0; ii<0x8001U; ++ii){
      bool const is_nextpower = (ii==nextpower);
      CAPTURE(ii);
      auto dut = Math::Discrete::nextpow2<u32>(ii);
      REQUIRE( nextpower == dut );
      if(is_nextpower){
        nextpower = Math::Boolean::ARITHSHL<u32>(nextpower,1);
      }
    }
  }

  SECTION("Math::Discrete::odd"){

  }

  SECTION("Math::Discrete::even"){

  }

  SECTION("Math::Discrete::leadingzeros"){

  }

  SECTION("Math::Discrete::udivceil<u16>"){
    auto const a = u16(GENERATE(take(150, random(0, 65535))));
    auto const b = u16(GENERATE(take(150, random(0, 65535))));

    auto ref = (b>0)?(a / b):(0);
         ref += ((a%b)>0)?(1):(0);

    auto dut = Math::Discrete::udivceil<u16>(a,b);
    auto dut2 = Math::Discrete::ceildiv<u16>(a,b);

    CAPTURE(a);
    CAPTURE(b);
    REQUIRE( ref == dut );
    REQUIRE( ref == dut2 );
  }

  SECTION("Math::Discrete::divide_by_shift<u16>"){
    auto const a = u16(GENERATE(take(150, random(0, 65535))));
    auto const b = u16(GENERATE(take(150, random(0, 65535))));

    auto ref = (b>0)?(a / b):(0);
    auto dut = Math::Discrete::divide_by_shift<u16>(a,b);

    CAPTURE(a);
    CAPTURE(b);

    REQUIRE( ref == dut );
  }

  SECTION("Math::Discrete::divide_by_shift<u16> with rounding"){
    auto const a = u16(GENERATE(take(150, random(0, 65535))));
    auto const b = u16(GENERATE(take(150, random(0, 65535))));

    auto ref = Math::Discrete::udivround<u16>(a,b);
    auto dut = Math::Discrete::divide_by_shift<u16>(a,b,true);

    CAPTURE(a);
    CAPTURE(b);

    REQUIRE( ref == dut );
  }

  //SECTION("Math::Discrete::divide_by_shift<u16> test"){
  //  {
  //    u16 a = 100;
  //    u16 b = 5;
  //    auto ref = a / b;
  //    auto dut = Math::Discrete::divide_by_shift<u16>(a,b);
  //    CAPTURE(a);
  //    CAPTURE(b);
  //    REQUIRE( ref == dut );
  //  }
  //  {
  //    u16 a = 100;
  //    u16 b = 7;
  //    auto ref = a / b;
  //    auto dut = Math::Discrete::divide_by_shift<u16>(a,b);
  //    CAPTURE(a);
  //    CAPTURE(b);
  //    REQUIRE( ref == dut );
  //  }
  //  {
  //    u16 a = 100;
  //    u16 b = 11;
  //    auto ref = a / b;
  //    auto dut = Math::Discrete::divide_by_shift<u16>(a,b);
  //    CAPTURE(a);
  //    CAPTURE(b);
  //    REQUIRE( ref == dut );
  //  }
  //  {
  //    u16 a = 100;
  //    u16 b = 13;
  //    auto ref = a / b;
  //    auto dut = Math::Discrete::divide_by_shift<u16>(a,b);
  //    CAPTURE(a);
  //    CAPTURE(b);
  //    REQUIRE( ref == dut );
  //  }
  //  {
  //    u16 a = 100;
  //    u16 b = 17;
  //    auto ref = a / b;
  //    auto dut = Math::Discrete::divide_by_shift<u16>(a,b);
  //    CAPTURE(a);
  //    CAPTURE(b);
  //    REQUIRE( ref == dut );
  //  }
  //  {
  //    u16 a = 10356;
  //    u16 b = 10356;
  //    auto ref = a / b;
  //    auto dut = Math::Discrete::divide_by_shift<u16>(a,b);
  //    CAPTURE(a);
  //    CAPTURE(b);
  //    REQUIRE( ref == dut );
  //  }
  //}

} //TestCase
