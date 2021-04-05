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

#include <algorithm>

#include "Stringhelper.h"
#include "bitmacros.h"

using namespace std;

//---

/**
 * @brief Utility::Strings::Smply - Generate Sting of multiple copies of String str count times
 * @param str
 * @param count
 * @return
 */
string Utility::Strings::Smply(string const& str, u32 const count){
  stringstream ss;
  for(u32 ii=0;ii<count;++ii){
    ss << str;
  }
  return ss.str();
}

/**
 * @brief Utility::Strings::depth2indent
 * @param depth
 * @return
 */
string Utility::Strings::depth2indent(u32 const depth){
  stringstream ss;
  for(u32 ii=0;ii<depth;++ii){
    ss << " ";
  }
  return ss.str();
}

/**
 * @brief Utility::Strings::comma2WS - Comma to Whitespace
 * @param str
 * @return
 */
string Utility::Strings::comma2WS(string const& str){
  string res(str);
  string::size_type pos = res.find(',');
  while(pos!=string::npos){
    res.replace(pos, 1, string(" "));
    pos = res.find(',');
  }
  return res;
}

/**
 * @brief Utility::Strings::replace - In String str1 replace pattern str2 with str3
 * @param str1
 * @param str2
 * @param str3
 * @return
 */
string Utility::Strings::replace(string const& str1, string const& str2, string const& str3){
  string::size_type pos = 0;
  string tstr(str1);
  for(string::iterator it = tstr.begin(); it != tstr.end();){
    pos = tstr.find(str2);
    if(pos==string::npos){
      it=tstr.end();
    }else{
      tstr.replace(pos,str2.size(),str3);
    }
  }
  return tstr;
}

//---

/**
 * @brief Utility::Strings::extfill - Fill String str with char ch until str.size() == len
 * @param str
 * @param ch
 * @param len
 * @return
 */
std::string Utility::Strings::extfill(std::string const& str, char const ch, u32 const len){
  stringstream ss;
  ss << str;
  if(len>str.size()){
    string fill;
    size_t const cnt = len-str.size();
    fill.append(cnt,ch);
    ss << fill;
  }
  return ss.str();
}

/**
 *
 */
std::string Utility::Strings::toupper(std::string const& str){
  string xstr = str;
  std::transform(xstr.begin(), xstr.end(), xstr.begin(), ::toupper);
  return xstr;
}

/**
 *
 */
std::string Utility::Strings::tolower(std::string const& str){
  string xstr = str;
  std::transform(xstr.begin(), xstr.end(), xstr.begin(), ::tolower);
  return xstr;
}
