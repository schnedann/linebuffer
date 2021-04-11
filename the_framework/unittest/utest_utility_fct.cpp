/****************************************
 * Includes
 ****************************************/
#include <iostream>
#include <iomanip>
#include <random>
#include <cmath>

#include "catch.hpp"

#include "dtypes.h"
#include "utility_fct.h"

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

TEST_CASE("Utility::Numbers","[utility,numbers]"){

  SECTION("Utility::Numbers::gethexdigitscount"){
    REQUIRE( 1 == Utility::Numbers::gethexdigitscount<u32>(0) );
    REQUIRE( 1 == Utility::Numbers::gethexdigitscount<u32>(15) );
    REQUIRE( 2 == Utility::Numbers::gethexdigitscount<u32>(16) );
    REQUIRE( 2 == Utility::Numbers::gethexdigitscount<u32>(255) );
    REQUIRE( 3 == Utility::Numbers::gethexdigitscount<u32>(256) );
    REQUIRE( 3 == Utility::Numbers::gethexdigitscount<u32>(4095) );
    REQUIRE( 4 == Utility::Numbers::gethexdigitscount<u32>(4096) );
    REQUIRE( 4 == Utility::Numbers::gethexdigitscount<u32>(65535) );
    REQUIRE( 5 == Utility::Numbers::gethexdigitscount<u32>(65536) );
    REQUIRE( 5 == Utility::Numbers::gethexdigitscount<u32>(1048575) );
    REQUIRE( 6 == Utility::Numbers::gethexdigitscount<u32>(1048576) );
    REQUIRE( 6 == Utility::Numbers::gethexdigitscount<u32>(16777215) );
  }

  SECTION("Utility::Numbers::estimatedecimalplaces"){
    REQUIRE( 1 == Utility::Numbers::gethexdigitscount<u32>(0) );
    REQUIRE( 1 == Utility::Numbers::gethexdigitscount<u32>(9) );
    REQUIRE( 2 == Utility::Numbers::gethexdigitscount<u32>(10) );
    REQUIRE( 2 == Utility::Numbers::gethexdigitscount<u32>(99) );
    REQUIRE( 3 == Utility::Numbers::gethexdigitscount<u32>(100) );
    REQUIRE( 3 == Utility::Numbers::gethexdigitscount<u32>(999) );
    REQUIRE( 4 == Utility::Numbers::gethexdigitscount<u32>(1000) );
    REQUIRE( 4 == Utility::Numbers::gethexdigitscount<u32>(9999) );
    REQUIRE( 5 == Utility::Numbers::gethexdigitscount<u32>(10000) );
    REQUIRE( 5 == Utility::Numbers::gethexdigitscount<u32>(99999) );
    REQUIRE( 6 == Utility::Numbers::gethexdigitscount<u32>(100000) );
    REQUIRE( 6 == Utility::Numbers::gethexdigitscount<u32>(999999) );
  }
}
