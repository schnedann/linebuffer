#include <iostream>
#include <iomanip>

#include "dtypes.h"
#include "gendata.h"
#include "crc_calc.h"
#include "hdlgenerate.h"
#include "paramodifiers.h"
#include "debug_hlp.h"

constexpr bool const USE_RANDOM = false;
constexpr bool const USE_LINEAR = true;

using namespace std;
using namespace Application;

int main(int argc pmUNUSED, char **argv pmUNUSED){

  CRCCalc cc;

  DBGOUT("Generate HDL (verilog) CRC")

//-----

  constexpr u16 const crc_poly = 0xC86Cu;
  DBGOUT("----------------------------------------")
  DBGOUT(PRNVAR(crc_poly))
  DBGOUT("----------------------------------------")
  cc.setpoly(crc_poly);

//-----

if(USE_RANDOM){
  auto rd = Utility::GenData::genrand(100);
  DBGOUT(Utility::Strings::print_array(rd.data(),rd.size()))
//-----
  DBGOUT("----------------------------------------")
//-----
  cc.init(0);
  DBGOUT(Utility::Strings::stradd<2>({"CRC: ",Utility::Strings::unum2str(cc.doblock(rd),Utility::Strings::conmode_t::asHEX)}))
//-----
  DBGOUT("========================================")
//-----
}

if(USE_LINEAR){
  auto rd = Utility::GenData::genlinear(1,1,25);
  DBGOUT(Utility::Strings::print_array(rd.data(),rd.size()))
//-----
  DBGOUT("----------------------------------------")
//-----
  cc.init(0xFFFFu);
  DBGOUT(Utility::Strings::stradd<2>({"CRC: ",Utility::Strings::unum2str(cc.doblock(rd),Utility::Strings::conmode_t::asHEX)}))
//-----
  DBGOUT("========================================")
//-----
}

/*
  DBGOUT("----------------------------------------")
  cout << "-- Poly 0x1021 -------------------------" << endl;
  DBGOUT("----------------------------------------")
  cc.setpoly(0x1021u);
//-----
#if RANDOM == 1
  gd.genrand(100);
  for(vector<unsigned char>::iterator it=rd.begin(); it!=rd.end(); ++it){
    cout << dec << setw(0) << setfill(' ') << (int)*it << " , ";
  }
  cout << endl;
//-----
  DBGOUT("----------------------------------------")
//-----
  cc.init(0);
  cout << "CRC: 0x" << hex << setw(4) << setfill('0') << cc.doblock(rd) << endl;
//-----
  DBGOUT("========================================")
//-----
#endif
#if LINEAR == 1
  rd = gd.genlinear(0,1,25);
  for(vector<unsigned char>::iterator it=rd.begin(); it!=rd.end(); ++it){
    cout << dec << setw(0) << setfill(' ') << (int)*it << " , ";
  }
  cout << endl;
//-----
  DBGOUT("----------------------------------------")
//-----
  cc.init(0xFFFFu);
  cout << "CRC: 0x" << hex << setw(4) << setfill('0') << cc.doblock(rd) << endl;
  cout << "iCRC: 0x" << hex << setw(4) << setfill('0') << cc.doblock(cc.addcrc(rd,0x1021u,0xFFFFu)) << endl;
#endif
*/
  //-----
  hdlgenerate hdlgen;
  hdlgen.setpoly(0xc86cu);
  cout << hdlgen.poly2str() << endl;
  cout << hdlgen.genhdl(0xc86cu) << endl;
  return 0;
}
