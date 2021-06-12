//#include <iostream>
#include <cstdint>
#include <array>
#include <random>

#include "catch.hpp"

#include "alternate_divide.h"

using namespace std;
using namespace Math::Alternate;

TEST_CASE("Math::Alternate Divide by shifts"){
  SECTION("1"){
    if(true){
      array<u8,3> divider = {0,1,3}; //1+2+8=11
      for(u64 ii=0; ii<50; ++ii){
        CAPTURE(ii);
        REQUIRE( (ii/11) == divide_by_shifts<u32, divider.size()>(ii,divider) );
      }
    }
  }

  SECTION("2"){ //--> Performance of Algo is really bad for large _a and small divider, expect massive runtimes...
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis(0, 0x7FFFFFFFul);

    if(false){
      array<u8,3> divider = {0,1,3}; //1+2+8=11
      for(u64 ii=0; ii<1000; ++ii){
        u32 a = dis(gen);
        CAPTURE(ii);
        CAPTURE(a);
        REQUIRE( (a/11) == divide_by_shifts<u32, divider.size()>(a,divider) );
      }
    }
  }
}

TEST_CASE("Divide by Substract"){
  SECTION("1"){
    if(true){
      for(u64 ii=0; ii<1000; ++ii){
        for(u64 ij=1; ij<1000; ++ij){
          CAPTURE(ii);
          CAPTURE(ij);
          REQUIRE( (ii/ij) == divide_by_substact<u16>(ii,ij) );
        }
      }
    }
  }

  SECTION("2"){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis_A(0, 0x7FFFFFFFul);
    std::uniform_int_distribution<> dis_B(1, 0x7FFFFFFFul);

    if(1){
      for(u64 ii=0; ii<250000; ++ii){
        u32 a = dis_A(gen);
        u32 b = dis_B(gen);

        CAPTURE(ii);
        CAPTURE(a);
        CAPTURE(b);
        REQUIRE( (a/b) == divide_by_substact<u32>(a,b) );
      }
    }
  }
}

TEST_CASE("Divide by Multiply"){
  SECTION("1"){
    if(true){
      for(u64 ii=0; ii<100; ++ii){
        for(u64 ij=1; ij<100; ++ij){
          CAPTURE(ii);
          CAPTURE(ij);
          REQUIRE( (ii/ij) == divide_by_mply<u8>(ii,ij) );
        }
      }
    }
  }

  SECTION("2"){
    if(true){
      for(u64 ii=0; ii<1000; ++ii){
        for(u64 ij=1; ij<1000; ++ij){
          CAPTURE(ii);
          CAPTURE(ij);
          REQUIRE( (ii/ij) == divide_by_mply<u16>(ii,ij) );
        }
      }
    }
  }

  SECTION("3"){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis_A(0, 0x7FFFFFFFul);
    std::uniform_int_distribution<> dis_B(1, 0x7FFFFFFFul);

    if(true){
      for(u64 ii=0; ii<250000; ++ii){
        u32 a = dis_A(gen);
        u32 b = dis_B(gen);

        CAPTURE(ii);
        CAPTURE(a);
        CAPTURE(b);
        REQUIRE( (a/b) == divide_by_mply<u32>(a,b) );
      }
    }
  }

  SECTION("DEBUG"){
    if(true){
      REQUIRE( 4 == divide_by_mply<u32>(1147029588,282962519) );
    }
  }
}

TEST_CASE("Russian peasant multiplication"){
  SECTION("1"){
    if(true){
      for(u64 ii=0; ii<255; ++ii){
        for(u64 ij=0; ij<255; ++ij){
          CAPTURE(ii);
          CAPTURE(ij);
          REQUIRE( (ii*ij) == multiply_Russian_peasant<u16>(ii,ij) );
        }
      }
    }
  }

  SECTION("2"){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<> dis_A(0, 0x7FFFFFFFul);
    std::uniform_int_distribution<> dis_B(0, 0x7FFFFFFFul);

    if(1){
      for(u64 ii=0; ii<500000; ++ii){
        u32 a = dis_A(gen);
        u32 b = dis_B(gen);

        CAPTURE(ii);
        CAPTURE(a);
        CAPTURE(b);
        REQUIRE( (a*b) == multiply_Russian_peasant<u32>(a,b) );
      }
    }
  }
}
