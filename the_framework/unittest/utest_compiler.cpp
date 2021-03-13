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

#include "catch.hpp"
#include "dtypes.h"
#include "bitmacros.h"
#include "endianness_detect.h"
#include "gccversion.h"

TEST_CASE("Compiler Math"){

  SECTION("shift negative number"){
    //We expect the sign always to be located in the MSB
    for(s8 x=Math::Boolean::__MIN_SIGNED<s8>(); x<Math::Boolean::__MAX_SIGNED<s8>(); ++x){
      CAPTURE(s16(x));
      for(u8 bits=1; bits<9; ++bits){
        CAPTURE(bits);
        if(x<0){
          {
            s8  ref = s8(u8(x) << bits);
            s8 test = s8(x << bits);
            REQUIRE( ref == test );
            CAPTURE(test);
            if(test<0) REQUIRE( (u8(test)&0x80u)==0x80u );
          }
          {
           s8  ref = s8(~((u8(~x)) >> bits));
           s8 test = s8(x >> bits);
           REQUIRE( s16(ref) == s16(test) );
           CAPTURE(test);
           if(test<0) REQUIRE( (u8(test)&0x80u)==0x80u );
          }
        }else{
          {
            s8  ref = s8(u8(x) << bits);
            s8 test = s8(x << bits);
            REQUIRE( ref == test );
          }
          {
            s8  ref = s8(u8(x) >> bits);
            s8 test = s8(x >> bits);
            REQUIRE( ref == test );
          }
        }
      }
    }
  }

  SECTION("overflow"){
    //We expect "normal overflow behavior"
    {
      u8 ref = 0xFFU;
      ++ref;
      REQUIRE( 0 == ref );
    }
    {
      u16 ref = 0xFFFFU;
      ++ref;
      REQUIRE( 0 == ref );
    }
    {
      u32 ref = 0xFFFFFFFFUL;
      ++ref;
      REQUIRE( 0 == ref );
    }
    {
      u64 ref = 0xFFFFFFFFFFFFFFFFULL;
      ++ref;
      REQUIRE( 0 == ref );
    }
  }

  SECTION("division round of neg. numbers"){
    //We expect rounding towards zero
    REQUIRE( -1 == (-3/2) );
  }
}

TEST_CASE("Compiler Datatypes"){

  SECTION("integers"){
    REQUIRE( sizeof( u8) << sizeof(u16) );
    REQUIRE( sizeof(u16) << sizeof(u32) );
    REQUIRE( sizeof(u32) << sizeof(u64) );

    REQUIRE( 1 == sizeof( u8) );
    REQUIRE( 2 == sizeof(u16) );
    REQUIRE( 4 == sizeof(u32) );
    REQUIRE( 8 == sizeof(u64) );

    REQUIRE( sizeof( s8) << sizeof(s16) );
    REQUIRE( sizeof(s16) << sizeof(s32) );
    REQUIRE( sizeof(s32) << sizeof(s64) );

    REQUIRE( 1 == sizeof( s8) );
    REQUIRE( 2 == sizeof(s16) );
    REQUIRE( 4 == sizeof(s32) );
    REQUIRE( 8 == sizeof(s64) );

    REQUIRE( 4 == sizeof(float) );
    REQUIRE( 8 == sizeof(double) );

    REQUIRE( 1 == sizeof(bool) );
  }
}

TEST_CASE("endianness-detect","[endianness]"){

  SECTION("1"){
    //We expect little Indian...
    //                                     *%
    //                                  #(***
    //                                &,****
    //                              %****,(
    //                             ***/****
    //                            //****/,.
    //                            %***/**(
    //                           /%*****#(
    //                          %*(/&
    //                          %%%%#%#%
    //                         /#%%%%%/
    //                         %#%%%&
    //                         %%*
    //         ,&&&&&&&&&&   %%%(
    //       %&&&&&&&&&&&&&&&/%.
    //     *%%%%%%%&%%%&&&&&&&&&(
    //    .%%%%%%%&%%%%&&%%%%%%%(
    //     ,&&&&&&&&%%%&%%%&&%%%*
    //   /*(#*%///(#&&&&&&&&&%%%
    //   (//#%%#/(//#&&&&&&&&&&
    //    (///((/(((/%&&&&&&&&
    //    #//(((//((/(&&&&&&/
    //     &%#((((((((//%&
    //       %/////(//#%%
    //          %##%(/&&%(
    //         &///(/&&&
    //       &/(///%%&&%
    //     *///(//(&&&&&/,
    //    %#/(////#(&&%*%
    //   ******,*##(&//%
    //    **,****,(((&&*%
    //    /#***,*,#/(((%,
    //    **#,***,#/%#(/
    //     %*/,***,%#%.
    //      #*****,%#,*
    //       ##***,%%,/
    //  ,((*%#*****(***#
    //&((///////%,/#****%
    //#&((#%%(((#%#*,(#
    REQUIRE( Enviroment::Endianness::endianness_t::ENDIAN_LITTLE == Enviroment::Endianness::endianness() );
  }
}

TEST_CASE("GCC Version"){
  SECTION("Screen Output"){
    std::cout << "GCC Version" << dGNUC_VERSION << "\n";
  }
}


