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

namespace utility{

namespace strings{

constexpr bool const asDEC = false;
constexpr bool const asHEX = true;

/**
 * Convert Number to String - decimal or hexadecimal
 */
template<class T> std::string unum2str(T const& num, bool const& dechex){
  Compile::Guards::IsUnsigned<T>();
  std::stringstream ss;
  if(dechex==asDEC){
    ss << num;
  }else{
    ss << "0x" << std::hex << num;
  }
  return ss.str();
}

/**
 * Convert String to Number - decimal or hexadecimal
 */
template<class T> T str2unum(std::string const& str, bool const& dechex){
  Compile::Guards::IsUnsigned<T>();
  T num;
  std::stringstream ss;

  if(dechex==asHEX){
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
 * Convert a Variable to a String...
 */
template<typename T> std::string to_string(std::string name, T x){
  std::stringstream ss;
  ss << name << ": ";
  bool is_8bit_integer = std::is_integral<T>::value && (sizeof(T)==1);
  if(is_8bit_integer){
    bool is_u = std::is_unsigned<T>::value;
    if(is_u){
      ss << u16(x);
    }else{
      ss << s16(x);
    }
  }else{
    ss << x;
  }
  return ss.str();
}

#define PRNVAR(_X) (utility::strings::to_string<decltype(_X)>((#_X),(_X)))

//-----

/**
 * Convert a Variable to a String - convert Integers as HexString...
 */
template<typename T> std::string to_hstring(std::string name, T x){
  std::stringstream ss;
  ss << name << ": ";
  bool is_int = std::is_integral<T>::value;
  bool is_8bit_integer = is_int && (sizeof(T)==1);
  if(is_int){
    if(is_8bit_integer){
      bool is_u = std::is_unsigned<T>::value;
      if(is_u){
        ss << "0x" << std::hex << u16(x);
      }else{
        ss << "0x" << std::hex << s16(x);
      }
    }else{
      ss << "0x" << std::hex << x;
    }
  }else{
    ss << x;
  }
  return ss.str();
}

#define PRNHEXVAR(_X) (utility::strings::to_hstring<decltype(_X)>((#_X),(_X)))

//-----

class Stringhelper
{
public:
  static std::string prnbin(u64 const& data,u8 const& length);
};

/****************************************
 * Generate Sting of multiple copies of itself
 ****************************************/
std::string Smply(std::string const&, u32 const&);

/****************************************
 * change Commas to WhiteSpace
 ****************************************/
std::string comma2WS(std::string const&);

/****************************************
 * indent String with WhiteSpace x Times
 ****************************************/
std::string depth2indent(u32 const&);

/****************************************
 * Replace all ocourences of String 2 in String 1
 ****************************************/
std::string replace(std::string const& ,std::string const& ,std::string const&);

//---

/**
 * @brief X_2hexstr - Convert unsigned Number _x to HexString
 */
template<class T> std::string X_2hexstr(T const& _x){
  Compile::Guards::IsUnsigned<T>();
  return static_cast<std::ostringstream*>( &(std::ostringstream() << std::hex << "0x" << _x) )->str();
}

/**
 * @brief X_2str - Convert Number _x to String in Field with Width w and fillchar f
 */
template<class T> std::string X_2str(T const& _x, int const& w, char const& f){
  Compile::Guards::isArithmetic<T>();
  return static_cast<std::ostringstream*>( &(std::ostringstream() << std::setw(w) << std::setfill(f) << _x) )->str();
}

/**
 * @brief str2_X - Convert String to type T
 */
template<class T> T str2_X(std::string& str){
  T res;
  std::istringstream(str)>>res;
  return res;
}

//---

/**
 * @brief unum2bin - Convert unsigned Integer 2 binary as String
 */
template<typename T> std::string unum2bin(T const& x, u8 const& bits){
  Compile::Guards::IsUnsigned<T>();
  std::string res;
  //u8 const rbits = ()?():();
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

static std::string extfill(std::string const&, char const&, u32 const&);

static std::string toupper(std::string const&);
static std::string tolower(std::string const&);

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

} //namespace

} //namespace

#endif // Stringhelper_H_
