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

#include <iostream>
#include <iomanip>
#include <limits>
#include <cmath>
#include <random>

#include "dtypes.h"
#include "bitmacros.h"

/*
#include "QNumber.h"
#include "general_math.h"
*/
//----- Helpers

#include "flowpoint_util.h"
#include "Stringhelper.h"

//----- Unit Testing

#include "catch.hpp"

using namespace std;
using namespace Math::Flowpoint;

TEST_CASE( "Helper: Stringhelper", "[helper]" ){
  SECTION( "ConfigConstants" ){

    REQUIRE( bool(utility::strings::conmode::asHEX) == true );
    REQUIRE( bool(utility::strings::conmode::asDEC) == false );
  }
  SECTION( "String <--> Number, Hexadecimal" ){
    auto mode = utility::strings::conmode::asHEX;
    auto tmp = utility::strings::str2unum<u16>("0xDEAD",mode);
    REQUIRE( tmp == 0xDEADu );

    std::string str = utility::strings::unum2str<u16>(static_cast<u16>(tmp),mode);
    REQUIRE( str.compare("0xdead") == 0 );
  }
  SECTION( "Print Binary Number" ){
    std::string str = utility::strings::prnbin(57005,16);
    REQUIRE( str.compare("1101111010101101") == 0 );
  }
  SECTION( "String <--> Number, Decimal" ){
    auto mode = utility::strings::conmode::asDEC;
    std::string str = utility::strings::unum2str<u16>(12345,mode);
    REQUIRE( str.compare("12345") == 0 );

    auto tmp = utility::strings::str2unum<u16>(str,mode);
    REQUIRE( 12345 == tmp );
  }

  //cout << "--------------------------------------------------" << "\n";
  return;
}

//-----

TEST_CASE( "Helper: Flowpoint", "[helper]" ){
  SECTION( "A" ){
    cout << " Section - A...";
/* Code doesnt work due Floating Point issues
    double increment  = (1.0/16);
    //double resolution = std::numeric_limits<double>::epsilon() * (1+ceil(increment / std::numeric_limits<double>::epsilon()));
    double resolution = increment*2.0; //std::numeric_limits<double>::epsilon();
    CAPTURE(increment);
    CAPTURE(resolution);
    double test = -1000.0;
    for(double cmpval=-1000.0; cmpval<1000.0; cmpval+=increment){
      test += increment;
      CAPTURE(cmpval);
      CAPTURE(test);
      CAPTURE(abs(test-cmpval));
      CAPTURE(((abs(test) < abs(cmpval) ? abs(cmpval) : abs(test)) * resolution));

      CAPTURE(Double_t(cmpval).Negative());
      CAPTURE(Double_t(cmpval).RawMantissa());
      CAPTURE(Double_t(cmpval).RawExponent());
      CAPTURE(Double_t(test).Negative());
      CAPTURE(Double_t(test).RawMantissa());
      CAPTURE(Double_t(test).RawExponent());
      CAPTURE(reinterpret_cast<s64*>(&cmpval)-reinterpret_cast<s64*>(&test));
      REQUIRE(flowpoint_util::approximatelyEqual(test,cmpval,resolution));
      //REQUIRE(flowpoint_util::AlmostEqual2sComplement(test,cmpval,static_cast<s64>(resolution)<<5));
      //test += increment;
    }
*/
    cout << " finished...\n";
    cout << "--------------------------------------------------" << "\n";
  }
  SECTION( "B" ){
    cout << " Section - B...";
    u32 count = 0;
    double ii_incr = 10015.357/9998.973;
    for(double ii=-1000.0; ii<1000.0; ii+=ii_incr){
      for(double ij=1e-12; ij<0.0001; ij*=10.0){
        double test = ii+ij;
        CAPTURE(count++);
        CAPTURE(ii);
        CAPTURE(ij);
        CAPTURE(test);
        REQUIRE(Math::Flowpoint::checkequal<double>(ii,test,ij,1e-6));
      }
    }
    cout << " finished...\n";
    cout << "--------------------------------------------------" << "\n";
  }
  SECTION( "C" ){
    cout << " Section - C...";
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<u64> dis(1, Math::Boolean::GETFULLMASK<u64>(64));

    for(u32 count=1; count<1e6; ++count){
      double ii   = static_cast<double>(dis(gen))/static_cast<double>(dis(gen));
      double tmp  = static_cast<double>(dis(gen))/static_cast<double>(dis(gen));
      double incr = std::nextafter(tmp,std::numeric_limits<double>::max());
      double ij   = ii+tmp;
      CAPTURE(count);
      CAPTURE(ii);
      CAPTURE(incr);
      CAPTURE(ij);
      REQUIRE(Math::Flowpoint::checkequal<double>(ii,ij,incr,1e-6));
    }
    cout << " finished...\n";
    cout << "--------------------------------------------------" << "\n";
  }
  SECTION( "D" ){
    cout << " Section - D...";
    cout << " finished...\n";
    cout << "--------------------------------------------------" << "\n";
  }

  //cout << "--------------------------------------------------" << "\n";
  return;
}

//-----
