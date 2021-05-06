#ifndef _HDLGenerate_H_
#define _HDLGenerate_H_

#include <string>
#include <sstream>
#include <vector>

#include "dtypes.h"

namespace Application{

class hdlgenerate{
private:
  //--- variables
  u8 crcwidth{16};
  u32 dbits;
  u32 cbits;
  u32 poly;
  u32 ival;
  std::vector<std::string> hdlcode;
  //--- methods

  void initgen(void);
public:
  hdlgenerate()=default;
  ~hdlgenerate()=default;
  std::string poly2str();
  std::string genhdl(u16);
  void setdbits(u32 const _v);
  void setcbits(u32 const _v);
  void setpoly( u32 const _v);
  void setival( u32 const _v);
};

} //namespace

#endif // _HDLGenerate_H_
