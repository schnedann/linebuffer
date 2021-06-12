#include "catch.hpp"

#include "dtypes.h"
#include "variable_guard.h"

TEST_CASE("Core::RuntimeGuards::variable_guard"){

  SECTION("Core::RuntimeGuards::variable_guard"){
    u32 dut = 0xabcdef;
    auto ref = dut;

    {
      //Freeze state of dut for outer scope
      Core::RuntimeGuards::variable_guard<u32> vg(&dut);
      dut = 0;
    }

    REQUIRE( ref == dut );
  }

} //TestCase
