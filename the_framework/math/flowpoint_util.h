/******************************************************************************/
/** Algorithms to calculate the Integer Log2                                 **/
/** developed , collected and / or implemented by                            **/
/** Danny Schneider, 2017-2021                                               **/
/******************************************************************************/

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

#ifndef FLOWPOINT_UTIL_H
#define FLOWPOINT_UTIL_H

#include <limits>
#include <cmath>

#include "dtypes.h"

namespace Math{

namespace Flowpoint{

/*
* The following definitions are from The art of computer programming by Knuth:
*/
template<class T> bool approximatelyEqual(T const& a, T const& b, T const& epsilon){
return abs(a - b) <= ( (abs(a) < abs(b) ? abs(b) : abs(a)) * epsilon);
}

template<class T> bool essentiallyEqual(T const& a, T const& b, T const& epsilon){
return abs(a - b) <= ( (abs(a) > abs(b) ? abs(b) : abs(a)) * epsilon);
}

template<class T> bool definitelyGreaterThan(T const& a, T const& b, T const& epsilon){
return (a - b) > ( (abs(a) < abs(b) ? abs(b) : abs(a)) * epsilon);
}

template<class T> bool definitelyLessThan(T const& a, T const& b, T const& epsilon){
return (b - a) > ( (abs(a) < abs(b) ? abs(b) : abs(a)) * epsilon);
}

//-----

/**
* @brief eps returns the distance from _x to the next larger (floating point) number
* @param _x
* @return
*/
template<class T> auto eps(T const& _x)->T{
T _y = std::nextafter(_x,std::numeric_limits<T>::max());
return _y-_x;
}

/**
* @brief How does the relative error between X and Y compare to eps(Y)?
* If "result" is small, then X and Y are close to each other,
* 1 is a very good value of equalness, 4-5 are resonable good, given that numerical errors can add up
* --> taken from https://de.mathworks.com/matlabcentral/answers/135291-can-i-compare-two-numbers-using-unit-in-the-last-place-ulps-in-matlab?requestedDomain=www.mathworks.com
* @return
*/
template<class T> auto estimatealmostequal(T const& _x,T const& _y) -> T{
  double u    = 0.0;
  double ey   = eps<T>(_y);
  double absy = abs(_y);
  if((absy!=0.0) && (ey!=0.0)){
    u = abs(_x-_y) / absy * ey;
  }else{
    u = abs(_x);
  }

  //cout << "U: " << u << "\n";
return u;
}

/**
 * @brief checkalmostequal - Distance Check
 * @param _x - number 1
 * @param _y - number 2
 * @param _d - distance bound
 */
template<class T> auto checkalmostequal(T const& _x,T const& _y,T const& _d) -> s8{
  s8 res = 0;

  //Larger or smaller?
  res += (_x>_y)?(1):(-1);

  //If Larger, check if it is larger by distance
  if(res>0){
    res += (_x>(_y+_d))?(0):(-1);
  }
  //If Smaller, check if it is smaller by distance
  if(res<0){
    res += (_y>(_x+_d))?(0):(1);
  }
  //Double check by callculating the difference and compare with the distance
  if(res>0){
    res += ((_x-_y)>_d)?(0):(-1);
  }
  //Double check by callculating the difference and compare with the distance
  if(res<0){
    res += ((_y-_x)>_d)?(0):(-1);
  }
  return res;
}

/**
* @brief Combined Equal check Methods
* @param _x - number 1
* @param _y - number 2
* @param _d - distance bound
* @param _u - equivalance factor
* @param true if numbers are equal within the definition
* @return
*/
template<class T> auto checkequal(T const& _x,T const& _y,T const& _d,T const& _u) -> bool{
bool res = true;
//Distance check between X & Y
res &= (checkalmostequal<T>(_x,_y,_d)==0)?(true):(false);
//Check if both numbers are "near" to each other
res &= (estimatealmostequal<T>(_x,_y)<=_u)?(true):(false); //
return res;
}

//-----

bool AlmostEqual2sComplement(float  A, float  B, s32 maxUlps);
bool AlmostEqual2sComplement(double A, double B, s64 maxUlps);


//-----

} //namespace

} //namespace

#endif // FLOWPOINT_UTIL_H

