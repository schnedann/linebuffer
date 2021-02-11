#include <iostream>
#include <string>

#include "catch.hpp"

#include "dtypes.h"
#include "linebuffer.h"

using namespace std;

TEST_CASE("linebuffer"){
  SECTION("1"){
    linebuffer lb;

    lb.add("1\n1");             //3
    lb.add("22\n22");           //5
    lb.add("333\n333");         //7
    lb.add("4444\n4444");       //9
    lb.add("55555\n55555");     //11
    lb.add("666666\n666666");   //13
    lb.add("7777777\n7777777"); //15

    REQUIRE( 63 == lb.size() );
  }
}
