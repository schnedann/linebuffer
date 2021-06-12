#include <iostream>
#include <string>
#include <type_traits>

#include "catch.hpp"

#include "dtypes.h"

using namespace std;

TEST_CASE("dtypes"){

  SECTION("typetraits - std::is_integral<>()"){
    REQUIRE( std::is_integral<u8>()  );
    REQUIRE( std::is_integral<s8>()  );
    REQUIRE( std::is_integral<u16>() );
    REQUIRE( std::is_integral<s16>() );
    REQUIRE( std::is_integral<u32>() );
    REQUIRE( std::is_integral<s32>() );
    REQUIRE( std::is_integral<u64>() );
    REQUIRE( std::is_integral<s64>() );
  }

  SECTION("typetraits - sizeof()"){
    REQUIRE( 1==sizeof(u8 ) );
    REQUIRE( 1==sizeof(s8 ) );
    REQUIRE( 2==sizeof(u16) );
    REQUIRE( 2==sizeof(s16) );
    REQUIRE( 4==sizeof(u32) );
    REQUIRE( 4==sizeof(s32) );
    REQUIRE( 8==sizeof(u64) );
    REQUIRE( 8==sizeof(s64) );

    REQUIRE( 1==sizeof(u8  const&) );
    REQUIRE( 1==sizeof(s8  const&) );
    REQUIRE( 2==sizeof(u16 const&) );
    REQUIRE( 2==sizeof(s16 const&) );
    REQUIRE( 4==sizeof(u32 const&) );
    REQUIRE( 4==sizeof(s32 const&) );
    REQUIRE( 8==sizeof(u64 const&) );
    REQUIRE( 8==sizeof(s64 const&) );
  }

  SECTION("typetraits - std::is_signed<>()"){
    REQUIRE( !std::is_signed<u8>()  );
    REQUIRE(  std::is_signed<s8>()  );
    REQUIRE( !std::is_signed<u16>() );
    REQUIRE(  std::is_signed<s16>() );
    REQUIRE( !std::is_signed<u32>() );
    REQUIRE(  std::is_signed<s32>() );
    REQUIRE( !std::is_signed<u64>() );
    REQUIRE(  std::is_signed<s64>() );
  }

  SECTION("typetraits - std::is_unsigned<>()"){
    REQUIRE(  std::is_unsigned<u8>()  );
    REQUIRE( !std::is_unsigned<s8>()  );
    REQUIRE(  std::is_unsigned<u16>() );
    REQUIRE( !std::is_unsigned<s16>() );
    REQUIRE(  std::is_unsigned<u32>() );
    REQUIRE( !std::is_unsigned<s32>() );
    REQUIRE(  std::is_unsigned<u64>() );
    REQUIRE( !std::is_unsigned<s64>() );
  }

  SECTION("typetraits - sizeof()"){
    REQUIRE( !std::is_reference<u8 >() );
    REQUIRE( !std::is_reference<s8 >() );
    REQUIRE( !std::is_reference<u16>() );
    REQUIRE( !std::is_reference<s16>() );
    REQUIRE( !std::is_reference<u32>() );
    REQUIRE( !std::is_reference<s32>() );
    REQUIRE( !std::is_reference<u64>() );
    REQUIRE( !std::is_reference<s64>() );

    REQUIRE( std::is_reference<u8  const&>() );
    REQUIRE( std::is_reference<s8  const&>() );
    REQUIRE( std::is_reference<u16 const&>() );
    REQUIRE( std::is_reference<s16 const&>() );
    REQUIRE( std::is_reference<u32 const&>() );
    REQUIRE( std::is_reference<s32 const&>() );
    REQUIRE( std::is_reference<u64 const&>() );
    REQUIRE( std::is_reference<s64 const&>() );
  }

  SECTION("typetraits - std::is_const<>()"){
    REQUIRE( !std::is_const<u8  const&>() );
    REQUIRE( !std::is_const<s8  const&>() );
    REQUIRE( !std::is_const<u16 const&>() );
    REQUIRE( !std::is_const<s16 const&>() );
    REQUIRE( !std::is_const<u32 const&>() );
    REQUIRE( !std::is_const<s32 const&>() );
    REQUIRE( !std::is_const<u64 const&>() );
    REQUIRE( !std::is_const<s64 const&>() );
  }

  SECTION("typetraits - std::is_const<>()"){
    REQUIRE( !std::is_const<u8  const&>() );
    REQUIRE( !std::is_const<s8  const&>() );
    REQUIRE( !std::is_const<u16 const&>() );
    REQUIRE( !std::is_const<s16 const&>() );
    REQUIRE( !std::is_const<u32 const&>() );
    REQUIRE( !std::is_const<s32 const&>() );
    REQUIRE( !std::is_const<u64 const&>() );
    REQUIRE( !std::is_const<s64 const&>() );
  }
}

//if_else_t<(sizeof(T)==1 && std::is_integral<T>() && std::is_signed<T>()   && std::is_reference<T>() && std::is_const<T>()),s16 const&,
