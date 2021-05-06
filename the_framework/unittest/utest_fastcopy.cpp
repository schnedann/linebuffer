#include <array>
#include <cstring>

#include "catch.hpp"

#include "dtypes.h"
#include "fastcopy.h"

using namespace std;

TEST_CASE("Algorithms::fastcopy"){

SECTION("Algorithms::fastcopy"){

  struct test_st{
    u8  _a;
    u16 _b;
    u32 _c;
  };
  using test_t = struct test_st;

  constexpr size_t const elements = 50;
  std::array<test_t,elements> ref;
  std::array<test_t,elements> source;

  u32 ii=0;
  for(auto& _x:ref){
    _x._a = ii++ % 0xffU;
    _x._b = ii++ % 0xffffU;
    _x._c = ii++ % 0xffffffffUL;
  }

  auto const bytes = (elements*sizeof(test_t));
  std::memcpy(source.data(),ref.data(),bytes);

  std::array<test_t,elements> target;
  Algorithms::fastcopy<test_t>(source.data(),target.data(),elements);

  auto cmpres = std::memcmp(ref.data(),target.data(),bytes);

  CAPTURE(bytes);
  CAPTURE(source);
  CAPTURE(target);

  REQUIRE( 0 == cmpres );
}

}
