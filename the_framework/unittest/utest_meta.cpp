/*
 * Copyright 2017-2021,Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <string>
#include <array>
#include <vector>
#include <type_traits>

#include "catch.hpp"

#include "dtypes.h"
#include "meta.h"

TEST_CASE("Meta"){

  SECTION("Constants::UINTMAX"){
    constexpr u8  const a = Meta::Constants::UINTMAX< u8>::value;
    constexpr u16 const b = Meta::Constants::UINTMAX<u16>::value;
    constexpr u32 const c = Meta::Constants::UINTMAX<u32>::value;
    constexpr u64 const d = Meta::Constants::UINTMAX<u64>::value;
    constexpr s8  const e = Meta::Constants::UINTMAX< s8>::value;
    constexpr s16 const f = Meta::Constants::UINTMAX<s16>::value;
    constexpr s32 const g = Meta::Constants::UINTMAX<s32>::value;
    constexpr s64 const h = Meta::Constants::UINTMAX<s64>::value;

    REQUIRE(  u8(0xFFu                ) == a);
    REQUIRE( u16(0xFFFFu              ) == b);
    REQUIRE( u32(0xFFFFFFFFul         ) == c);
    REQUIRE( u64(0xFFFFFFFFFFFFFFFFull) == d);
    REQUIRE(  s8(0xFFu                ) == e);
    REQUIRE( s16(0xFFFFu              ) == f);
    REQUIRE( s32(0xFFFFFFFFul         ) == g);
    REQUIRE( s64(0xFFFFFFFFFFFFFFFFull) == h);
  }

/*
  SECTION("Math::Multiply"){
    constexpr u8 const a = Meta::Math::POWER<u8,2,11>::value;
    constexpr u8 const b = Meta::Math::CEILDIV<u8,a,3>::value;
  }*/

  SECTION("Math::SquareRoot_Heron"){
    constexpr u8 const a = Meta::Math::SquareRoot_Heron<u8,144>::value;
    REQUIRE( 12 == a);
    constexpr u8 const b = Meta::Math::SquareRoot_Heron<u8,168>::value;
    REQUIRE( 12 == b);
    constexpr u8 const c = Meta::Math::SquareRoot_Heron<u8,169>::value;
    REQUIRE( 13 == c);
  }

  SECTION("Math::Fibonacci"){
    std::array<u64,20> fseries = {
        1,   1,   2,   3,   5,   8,  13,  21,  34,  55,
       89, 144, 233, 377, 610, 987,1597,2584,4181,6765
    };

    /*constexpr u8 const f1 = Meta::Math::Fibonacci<u8,1>::result;
    REQUIRE( fseries[0] == f1);
    constexpr u8 const f2 = Meta::Math::Fibonacci<u8,2>::result;
    REQUIRE( fseries[1] == f2);*/
    constexpr u8 const f3 = Meta::Math::Fibonacci<u8,3>::result;
    REQUIRE( fseries[2] == f3);
    constexpr u8 const f4 = Meta::Math::Fibonacci<u8,4>::result;
    REQUIRE( fseries[3] == f4);
    constexpr u8 const f5 = Meta::Math::Fibonacci<u8,5>::result;
    REQUIRE( fseries[4] == f5);
    constexpr u8 const f6 = Meta::Math::Fibonacci<u8,6>::result;
    REQUIRE( fseries[5] == f6);
    constexpr u8 const f7 = Meta::Math::Fibonacci<u8,7>::result;
    REQUIRE( fseries[6] == f7);
    constexpr u8 const f8 = Meta::Math::Fibonacci<u8,8>::result;
    REQUIRE( fseries[7] == f8);
    constexpr u8 const f9 = Meta::Math::Fibonacci<u8,9>::result;
    REQUIRE( fseries[8] == f9);
    constexpr u8 const f10 = Meta::Math::Fibonacci<u8,10>::result;
    REQUIRE( fseries[9] == f10);
    constexpr u8 const f11 = Meta::Math::Fibonacci<u8,11>::result;
    REQUIRE( fseries[10] == f11);
    constexpr u8 const f12 = Meta::Math::Fibonacci<u8,12>::result;
    REQUIRE( fseries[11] == f12);
    constexpr u16 const f13 = Meta::Math::Fibonacci<u16,13>::result;
    REQUIRE( fseries[12] == f13);
    constexpr u16 const f14 = Meta::Math::Fibonacci<u16,14>::result;
    REQUIRE( fseries[13] == f14);
    constexpr u16 const f15 = Meta::Math::Fibonacci<u16,15>::result;
    REQUIRE( fseries[14] == f15);
    constexpr u16 const f16 = Meta::Math::Fibonacci<u16,16>::result;
    REQUIRE( fseries[15] == f16);
    constexpr u16 const f17 = Meta::Math::Fibonacci<u16,17>::result;
    REQUIRE( fseries[16] == f17);
    constexpr u16 const f18 = Meta::Math::Fibonacci<u16,18>::result;
    REQUIRE( fseries[17] == f18);
    constexpr u16 const f19 = Meta::Math::Fibonacci<u16,19>::result;
    REQUIRE( fseries[18] == f19);
    constexpr u16 const f20 = Meta::Math::Fibonacci<u16,20>::result;
    REQUIRE( fseries[19] == f20);
  }

  SECTION("FLOOR_LOG2"){
    REQUIRE( 0 == Meta::Math::FLOOR_LOG2<  0>::value );
    REQUIRE( 0 == Meta::Math::FLOOR_LOG2<  1>::value );
    REQUIRE( 1 == Meta::Math::FLOOR_LOG2<  2>::value );
    REQUIRE( 1 == Meta::Math::FLOOR_LOG2<  3>::value );
    REQUIRE( 2 == Meta::Math::FLOOR_LOG2<  4>::value );
    REQUIRE( 2 == Meta::Math::FLOOR_LOG2<  7>::value );
    REQUIRE( 3 == Meta::Math::FLOOR_LOG2<  8>::value );
    REQUIRE( 3 == Meta::Math::FLOOR_LOG2< 15>::value );
    REQUIRE( 4 == Meta::Math::FLOOR_LOG2< 16>::value );
    REQUIRE( 4 == Meta::Math::FLOOR_LOG2< 31>::value );
    REQUIRE( 5 == Meta::Math::FLOOR_LOG2< 32>::value );
    REQUIRE( 5 == Meta::Math::FLOOR_LOG2< 63>::value );
    REQUIRE( 6 == Meta::Math::FLOOR_LOG2< 64>::value );
    REQUIRE( 6 == Meta::Math::FLOOR_LOG2<127>::value );
    REQUIRE( 7 == Meta::Math::FLOOR_LOG2<128>::value );
  }

  SECTION("CEIL_LOG2"){
    REQUIRE( 0 == Meta::Math::CEIL_LOG2<  0>::value );
    REQUIRE( 0 == Meta::Math::CEIL_LOG2<  1>::value );
    REQUIRE( 1 == Meta::Math::CEIL_LOG2<  2>::value );
    REQUIRE( 2 == Meta::Math::CEIL_LOG2<  3>::value );
    REQUIRE( 2 == Meta::Math::CEIL_LOG2<  4>::value );
    REQUIRE( 3 == Meta::Math::CEIL_LOG2<  7>::value );
    REQUIRE( 3 == Meta::Math::CEIL_LOG2<  8>::value );
    REQUIRE( 4 == Meta::Math::CEIL_LOG2< 15>::value );
    REQUIRE( 4 == Meta::Math::CEIL_LOG2< 16>::value );
    REQUIRE( 5 == Meta::Math::CEIL_LOG2< 31>::value );
    REQUIRE( 5 == Meta::Math::CEIL_LOG2< 32>::value );
    REQUIRE( 6 == Meta::Math::CEIL_LOG2< 63>::value );
    REQUIRE( 6 == Meta::Math::CEIL_LOG2< 64>::value );
    REQUIRE( 7 == Meta::Math::CEIL_LOG2<127>::value );
    REQUIRE( 7 == Meta::Math::CEIL_LOG2<128>::value );
  }

  SECTION("Power"){
    REQUIRE(   144 == Meta::Math::POWER<12, 2>::value);
    REQUIRE( 59049 == Meta::Math::POWER< 3,10>::value);
    REQUIRE(  1000 == Meta::Math::POWER<10, 3>::value);
    REQUIRE(   625 == Meta::Math::POWER<25, 2>::value);
    REQUIRE(456976 == Meta::Math::POWER<26, 4>::value);
  }

  SECTION("Ceildiv"){
  //REQUIRE( 2 == Meta::Math::CEILDIV<u16,    3,    0>::value);
    REQUIRE( 2 == Meta::Math::CEILDIV<u16,    3,    2>::value);
    REQUIRE( 8 == Meta::Math::CEILDIV<u16,   22,    3>::value);
    REQUIRE( 8 == Meta::Math::CEILDIV<u16,   23,    3>::value);
    REQUIRE(12 == Meta::Math::CEILDIV<u16,   23,    2>::value);
    REQUIRE( 2 == Meta::Math::CEILDIV<u16,30000,29999>::value);
  }

  SECTION("Meta::Varadic::sum"){
    auto dut = Meta::Varadic::sum<std::string,std::string,std::string>("Hello"," ","World");
    auto ref = "Hello World";
    REQUIRE( 0==dut.compare(ref) );
  }

  SECTION("Meta::Varadic::bswap"){
    {
      auto dut = Meta::Varadic::bswap<u16>(0x1234U);
      auto ref = 0x3412U;
      REQUIRE( dut == ref );
    }
    {
      auto dut = Meta::Varadic::bswap<u32>(0xABCD1234UL);
      auto ref = 0x3412CDABUL;
      REQUIRE( dut == ref );
    }
    {
      auto dut = Meta::Varadic::bswap<u64>(0x0123456789abcdefULL);
      auto ref = 0xefcdab8967452301ULL;
      REQUIRE( dut == ref );
    }
  }

  SECTION("Meta::Math::DISCRETE<>::allbitsset"){
    /*REQUIRE(Meta::Math::DISCRETE< u8>::allbitsset ==  u8(-1));
    REQUIRE(Meta::Math::DISCRETE<u16>::allbitsset == u16(-1));
    REQUIRE(Meta::Math::DISCRETE<u32>::allbitsset == u32(-1));
    REQUIRE(Meta::Math::DISCRETE<u64>::allbitsset == u64(-1));*/
  }

  SECTION("Meta::Math::DISCRETE<u16>::isPrime"){
    {
      std::array<u16,100> set = {
        2,  3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
        89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,
        211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,
        349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,
        487,491,499,503,509,521,523,541
      };

      for(auto prime:set){
        CAPTURE( prime );
        REQUIRE( Meta::Math::Discrete<u16>::isPrime(prime) );
        if(prime>3) REQUIRE( !Meta::Math::Discrete<u16>::isPrime(prime-1) );
        if(prime>3) REQUIRE( !Meta::Math::Discrete<u16>::isPrime(prime+1) );
      }
    }
    {
      bool ip = Meta::Math::Discrete<u32>::isPrime(9999991);
      REQUIRE(ip);
    }
  }

  SECTION("Meta::Varadic::print_container"){
    std::vector<u16> set = {
      2,  3,  5,  7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83,
      89, 97,101,103,107,109,113,127,131,137,139,149,151,157,163,167,173,179,181,191,193,197,199,
      211,223,227,229,233,239,241,251,257,263,269,271,277,281,283,293,307,311,313,317,331,337,347,
      349,353,359,367,373,379,383,389,397,401,409,419,421,431,433,439,443,449,457,461,463,467,479,
      487,491,499,503,509,521,523,541
    };
    Meta::Varadic::print_container<std::vector,u16>(set);
  }

  SECTION("Meta::Types::replace8bitint<T>::type"){
    REQUIRE( std::is_same<u16,typename Meta::Types::replace8bitint<u8>::type>::value );
    REQUIRE( std::is_same<s16,typename Meta::Types::replace8bitint<s8>::type>::value );

    REQUIRE( std::is_same<u16,typename Meta::Types::replace8bitint<u16>::type>::value );
    REQUIRE( std::is_same<s16,typename Meta::Types::replace8bitint<s16>::type>::value );

    REQUIRE( std::is_same<u32,typename Meta::Types::replace8bitint<u32>::type>::value );
    REQUIRE( std::is_same<s32,typename Meta::Types::replace8bitint<s32>::type>::value );

    //REQUIRE( std::is_same<u8,Meta::Types::replace8bitint_t<u8 const&>>::value );
    //REQUIRE( std::is_same<u16,Meta::Types::replace8bitint_t<u8 const&>>::value );
    //REQUIRE( std::is_same<s16,Meta::Types::replace8bitint_t<s8 const&>>::value );
    //
    //REQUIRE( std::is_same<u16,Meta::Types::replace8bitint_t<u16 const&>>::value );
    //REQUIRE( std::is_same<s16,Meta::Types::replace8bitint_t<s16 const&>>::value );
    //
    //REQUIRE( std::is_same<u32,Meta::Types::replace8bitint_t<u32 const&>>::value );
    //REQUIRE( std::is_same<s32,Meta::Types::replace8bitint_t<s32 const&>>::value );
  }

}
