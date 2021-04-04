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

TEST_CASE("Math::Discrete","[math discrete]"){

  SECTION("Math::Discrete::median_of_three"){
    REQUIRE( 2 == Math::Discrete::median_of_three(1,2,3));
    REQUIRE( 2 == Math::Discrete::median_of_three(2,3,1));
    REQUIRE( 2 == Math::Discrete::median_of_three(3,1,2));

    REQUIRE( 2 == Math::Discrete::median_of_three(1,3,2));
    REQUIRE( 2 == Math::Discrete::median_of_three(3,2,1));
    REQUIRE( 2 == Math::Discrete::median_of_three(2,1,3));

    REQUIRE( 2 == Math::Discrete::median_of_three(2,1,3));
    REQUIRE( 2 == Math::Discrete::median_of_three(1,3,2));
    REQUIRE( 2 == Math::Discrete::median_of_three(3,2,1));
  }

  SECTION("Math::Discrete::log2 1/3"){
    array<u8,50> res{};
    for(u64 ii=0; ii<res.size(); ++ii){
      res[ii] = u8(Math::Discrete::log2<u64>(ii));
    }
    Utility::Strings::print_array<u8>(res.data(),res.size());
  }

  SECTION("Math::Discrete::log2 2/3"){
    {
      //Compare log2 from stdlib with own implementation

      /* http://www.cplusplus.com/doc/tutorial/typecasting/
       * If the conversion is from a floating-point type to an integer type,
       * the value is truncated (the decimal part is removed). If the result
       * lies outside the range of representable values by the type,
       * the conversion causes undefined behavior.
       */

      for(u64 ii=1; ii>0; ii<<=1){
        CAPTURE(ii);
        auto res1 = Math::Discrete::log2<u64>(ii);
        auto res2 = u64(std::log2(ii));
        REQUIRE(res1==res2);
      }
    }
  }

  SECTION("Math::Discrete::log2 3/3"){
//TODO
    /*{
      for(u64 ii=1; ii>0; ii=ii*2+1){
        CAPTURE(ii);
        auto res1 = Math::Discrete::log2<u64>(ii);
        double res_i = std::round(std::log2(ii)); //std::round()
        CAPTURE(res_i);
        auto res2 = u64(res_i);
        REQUIRE(res1==res2);
      }
    }*/
  }

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

  SECTION("Math::Discrete::odd"){

  }

  SECTION("Math::Discrete::even"){

  }

  SECTION("Math::Discrete::leadingzeros"){

  }

}
