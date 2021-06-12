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

#ifndef Stringhelper_H
#define Stringhelper_H

#include <string>
#include <sstream>
#include <iomanip>
#include <array>
#include <typeinfo>
#include <bitset>
#if defined(__GNUC__)
  #include <cxxabi.h>
#endif

#include "dtypes.h"
#include "compile_guards.h"
#include "bitmacros.h"
#include "iterators.h"
#include "meta.h"
#include "math_discrete.h"

namespace Utility{

namespace Strings{

//without copying the string
template<std::size_t N> std::string make_string_from_literal(const char(&s)[N]){
  return std::string(s, N-1);  // -1 for last '\0' character
}

/**
 * @brief Compose String from a list of Strings
 */
template<size_t N> std::string stradd(std::array<std::string,N> const list, bool const with_space=false){
  std::stringstream ss;
  for(auto str:list){
    ss << str;
    if(with_space) ss << " ";
  }
  ss << "\n";
  return ss.str();
}

#define INDENT(_x)  (Utility::Strings::stradd<2>({"  ",_x}))
#define ERROR(_x)   (Utility::Strings::stradd<2>({"Error  :  ",_x}))
#define WARNING(_x) (Utility::Strings::stradd<2>({"Warning:  ",_x}))

//-----


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
 * @brief demangle - Convert mangled Name to an unmangled name
 * @param mangled
 * @return
 */
std::string demangle(Core::Container::citerator_t<char> mangled);

/**
 * @brief to_string - Convert a Variable of any Type to String as long as an known conversion exists
 * @note signed and unsigned 8Bit Integers are handled as 16Bit values to prevent char output
 */
template<typename T> std::string to_string(std::string const& name, T const& _x){
  std::stringstream ss;
  using repl_t = typename Meta::Types::replace8bitint_t<T>;
  ss << demangle(typeid(T).name()) << " " << name << ": " << repl_t(_x);
  return ss.str();
}

/**
 * @brief PRNVAR - Macro to Convert any variable to an String, including output of the variable name
 */
#define PRNVAR(_X) (Utility::Strings::to_string<decltype(_X)>((#_X),(_X)))

//-----

/**
 * @brief to_hstring - Convert a Variable of any Type to String as long as an known conversion exists
 * @note signed and unsigned 8Bit Integers are handled as 16Bit values to prevent char output,
 *       also any integer is converted in Hexadecimal notation
 */
template<typename T> std::string to_hstring(std::string const& name, T const& _x){
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
#define PRNHEXVAR(_X) (Utility::Strings::to_hstring<decltype(_X)>((#_X),(_X)))

//-----

/**
 * @brief Utility::Strings::Stringhelper::prnbin - Unsigned Integer Number to Binary String
 * Convert a Numer to a binary String with Zeros and Ones
 * @param data
 * @param length
 * @return
 */
template<typename T> std::string prnbin(T const data, u8 const length = Math::Boolean::GETBITSOFTYPE<T>()){
  Compile::Guards::IsInteger<T>();
  std::stringstream ss;
  if(length>0){
    auto mask = Math::Boolean::GETMASKBIT<T>(length-1);
    while(mask>0){
      ss << (((data & mask) > 0)?("1"):("0"));
      mask >>= 1;
    }
  }
  return ss.str();
}

/**
 *
 */
template<typename T, std::size_t N=Math::Boolean::GETBITSOFTYPE<T>()> std::string prnbin_bitset(T const data){
  Compile::Guards::IsInteger<T>();
  std::stringstream ss;
  ss << std::bitset<N>(data);
  return ss.str();
}

#define PRNBIN(_X)       (Utility::Strings::prnbin<decltype(_X)>(_X))
#define PRNBINVAR(_X,_b) (Utility::Strings::stradd<3>({#_X,": ",Utility::Strings::prnbin<decltype(_X)>((_X),(_b))}))

//-----

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

#define VAR2STR(_x) (Utility::Strings::X_2str<decltype(_x)>(_x))

/**
 * @brief str2_X - Convert String to type T
 */
template<typename T> T str2_X(std::string const& str){
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
template<typename T> std::string print_array_Line(T data[], size_t const size){
  std::stringstream ss;
  ss << "|";
  for(size_t ii = 0; ii < size; ++ii){
    ss << data[ii] << "|";
  }
  ss << "\n";
  return ss.str();
}


/**
 * @brief print_array
 */
template<typename T> std::string print_array(Core::Container::citerator_t<T> ptr, size_t const size, size_t const elem_per_line=10){
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

/**
 * @brief print_array
 */
template<typename T, size_t N> std::string print_array(T const data[N]){
  return print_array(&data, N);
}

//-----



//-----

} //namespace

} //namespace

#endif // Stringhelper_H
