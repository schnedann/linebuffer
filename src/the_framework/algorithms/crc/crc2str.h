#ifndef _CRC2STR_H_
#define _CRC2STR_H_

#include <iostream>
//#include <iomanip>
#include <string>
#include <sstream>

#include "bitmacros.h"
#include "dtypes.h"

namespace stdext
{

class crc2str
{
private:
  /*crc2str(const crc2str& rhs);
  crc2str& operator=(const crc2str& rhs);*/

public:
  crc2str();
  virtual ~crc2str();

  template<class T> static auto poly2str(T const& poly)->std::string{
    std::stringstream ss;
    //---
    //ss << "1";
    bool first = true;
    for(int ii=0;ii<(int)(sizeof(T)<<3);++ii){
      if(mGetBit(poly,ii)>0){
        if(first==true){
          ss << "x^" << (ii);
          first = false;
        }else{
          ss << "+x^" << (ii);
        }
      }
    }
    return ss.str();
  }

};

}

#endif // _CRC2STR_H_
