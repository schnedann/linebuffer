#ifndef _CRCCalc_H_
#define _CRCCalc_H_

#include <vector>

#include "dtypes.h"

namespace std
{

class CRCCalc{
  private:
  u16 crc;  //CRC Bitshift-Register
  u16 poly;

  public:
  CRCCalc();
  ~CRCCalc();
  void init(u16);
  void setpoly(u16);
  u16 doblock(vector<u8>);
  u16 dobyte(u8);
  u16 alt01(u8 data);
  vector<u8> addcrc(vector<u8>, u16, u16);
  u16 checkinvert();
};

}

#endif // _CRCCalc_H_
