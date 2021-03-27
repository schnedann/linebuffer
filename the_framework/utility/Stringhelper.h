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

#ifndef Stringhelper_H_
#define Stringhelper_H_

#include <string>
#include <sstream>
#include <iomanip>

#include "dtypes.h"
#include "compile_guards.h"
#include "iterators.h"
#include "meta.h"
#include "math_discrete.h"

namespace utility{

namespace strings{

enum class conmode:bool{
  asDEC = false,
  asHEX = true
};
using conmode_t = enum conmode;

/**
 * Convert Number to String - decimal or hexadecimal
 */
template<class T> std::string unum2str(T const& num, conmode_t const dechex){
  Compile::Guards::IsUnsigned<T>();
  using insert_type_t = typename Meta::Types::replace8bitint<T>::type;
  std::stringstream ss;
  if(dechex==conmode::asDEC){
    ss << insert_type_t(num);
  }else{
    ss << "0x" << std::hex << insert_type_t(num);
  }
  return ss.str();
}

/**
 * Convert String to Number - decimal or hexadecimal
 */
template<class T> T str2unum(std::string const& str, conmode_t const dechex){
  Compile::Guards::IsUnsigned<T>();
  T num;
  std::stringstream ss;

  if(dechex==conmode::asHEX){
    size_t pos = str.find("0x",0);
    std::string croped = str.substr(pos,(str.length()-pos));
     ss << croped;
     ss >> std::hex >> num;
  }else{
     ss << str;
     ss >> num;
  }
  return num;
}

//-----

/**
 * @brief to_string - Convert a Variable of any Type to String as long as an known conversion exists
 * @note signed and unsigned 8Bit Integers are handled as 16Bit values to prevent char output
 */
template<typename T> std::string to_string(std::string name, T const& _x){
  std::stringstream ss;
  using insert_type_t = typename Meta::Types::replace8bitint<T>::type;
  ss << name << ": " << insert_type_t(_x);
  return ss.str();
}

/**
 * @brief PRNVAR - Macro to Convert any variable to an String, including output of the variable name
 */
#define PRNVAR(_X) (utility::strings::to_string<decltype(_X)>((#_X),(_X)))

//-----

/**
 * @brief to_hstring - Convert a Variable of any Type to String as long as an known conversion exists
 * @note signed and unsigned 8Bit Integers are handled as 16Bit values to prevent char output,
 *       also any integer is converted in Hexadecimal notation
 */
template<typename T> std::string to_hstring(std::string name, T const& _x){
  std::stringstream ss;
  using insert_type_t = typename Meta::Types::replace8bitint<T>::type;
  constexpr bool const is_int = std::is_integral<T>::value;
  if(is_int){
    ss << name << ": 0x" << std::hex << insert_type_t(_x);
  }else{
    ss << name << ": " << _x;
  }
  return ss.str();
}

/**
 * @brief PRNHEXVAR - Macro to Convert any variable to an (hex)String, including output of the variable name
 */
#define PRNHEXVAR(_X) (utility::strings::to_hstring<decltype(_X)>((#_X),(_X)))

//-----

std::string prnbin(u64 const data, u8 const length);

/****************************************
 * Generate Sting of multiple copies of itself
 ****************************************/
std::string Smply(std::string const& str, u32 const count);

/****************************************
 * indent String with WhiteSpace x Times
 ****************************************/
std::string depth2indent(u32 const depth);

/****************************************
 * change Commas to WhiteSpace
 ****************************************/
std::string comma2WS(std::string const& str);

/****************************************
 * Replace all ocourences of String 2 in String 1
 ****************************************/
std::string replace(std::string const& str1, std::string const& str2, std::string const& str3);

//---

/**
 * @brief X_2hexstr - Convert unsigned Number _x to HexString
 */
template<typename  T> std::string X_2hexstr(T const& _x){
  Compile::Guards::IsUnsigned<T>();
  using insert_type_t = typename Meta::Types::replace8bitint<T>::type;
  return static_cast<std::ostringstream*>( &(std::ostringstream() << std::hex << "0x" << insert_type_t(_x)) )->str();
}

/**
 * @brief X_2str - Convert Number _x to String in Field with Width w and fillchar f
 */
template<typename T> std::string X_2str(T const& _x, int const w=0, char const f=' '){
  Compile::Guards::isArithmetic<T>();
  using insert_type_t = typename Meta::Types::replace8bitint<T>::type;
  return static_cast<std::ostringstream*>( &(std::ostringstream() << std::setw(w) << std::setfill(f) << insert_type_t(_x)) )->str();
}

/**
 * @brief str2_X - Convert String to type T
 */
template<typename T> T str2_X(std::string& str){
  T res;
  std::istringstream(str)>>res;
  return res;
}

//---

/**
 * @brief unum2bin - Convert unsigned Integer 2 binary as String
 */
template<typename T> std::string unum2bin(T const& x, u8 const bits){
  Compile::Guards::IsUnsigned<T>();
  std::string res;
  res.resize(bits);
  u32 v = x;
  for(u8 ii=0; ii<bits; ++ii){
    res[ii] = ((v&1)>0)?('1'):('0');
    v>>=1;
  }
  return res;
}

/**
 * Unsigned Integer Number to Binary String
 */
/*template<typename T> string im_prnbin(u64 data,u8 length){
  stringstream ss;
  if(length>0){
    u64 mask = dMASK_MSB(length);
    while(mask>0){
      ss << (((data & mask) > 0)?("1"):("0"));
      mask >>= 1;
    }
  }
  return ss.str();
  }*/

std::string extfill(std::string const& str, char const ch, u32 const len);

std::string toupper(std::string const& str);
std::string tolower(std::string const& str);

//---

/**
 *  Print all Elements of a Array in one single Line divided by a '|'
 */
template<typename T> std::string print_array_Line(T data[], size_t size){
  std::stringstream ss;
  ss << "|";
  for(size_t ii = 0; ii < size; ++ii){
    ss << data[ii] << "|";
  }
  ss << "\n";
  return ss.str();
}



template<typename T> std::string print_array(Core::Container::citerator_t<T> ptr, size_t size, size_t elem_per_line=10){
  std::stringstream ss;
  u64 ii=1;
  for(u64 ij=0; ij<size; ++ij){
    ss << "[" << ij << "|" << X_2str<T>(ptr[ij]) << "]";
    if(ii==elem_per_line){
      ss << "\n";
      ii=0;
    }else{
      ss << ",";
    }
    ++ii;
  }
  ss << "\n";
  return ss.str();
}

template<typename T, size_t N> std::string print_array(T data[N]){
  return print_array(&data, N);
}

//-----

/**
 * Convert a Numer to a binary String with Zeros and Ones
 */
template<typename T> std::string prnbin(T data, u8 length = Math::Boolean::GETBITSOFTYPE<T>()){
  std::stringstream ss;
  if(length>0){
    auto mask = Math::Boolean::GETMASKBIT<u64>(length-1);
    while(mask>0){
      ss << (((data & mask) > 0)?("1"):("0"));
      mask >>= 1;
    }
  }
  return ss.str();
}

//-----

} //namespace

} //namespace

#endif // Stringhelper_H_
