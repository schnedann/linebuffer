#include <iostream>
#include <iomanip>

#include "crc_calc.h"
#include "bitmacros.h"
#include "bitreverse.h"
#include "utility_fct.h"

namespace std
{

CRCCalc::CRCCalc()
{
}

CRCCalc::~CRCCalc()
{
}

//------------------------------------------------------------

/**
 *
 */
void CRCCalc::init(u16 v){
  crc = v;
  return;
}

/**
 *
 */
void CRCCalc::setpoly(u16 p){
  poly = p;
  return;
}

/**
 *
 */
u16 CRCCalc::doblock(vector<u8> in){
  u16 res;
  //int ii=0;
  for(vector<u8>::iterator it=in.begin(); it!=in.end(); ++it){
    res = dobyte(*it);
    //cout << dec << setw(4) << setfill(' ') << ii++ << ": 0x" << hex << setw(4) << setfill('0') << res << endl;
    //cout << "Checkinvert:" << checkinvert() << endl;
  }
  return res;
}

/**
 *
 */
u16 CRCCalc::dobyte(u8 data){
  u16 tmp;
  for(int ii=0; ii<8; ++ii){
    //highest Bit in  crc shiftregister
    //unequal to current data Bit?
    tmp = (((crc >> 15) ^ data) & 0x0001);
    //shift crc register left
    crc <<= 1;
    //Make sure lowest Bit is zero
    crc &= 0xFFFEu;
    if(tmp > 0){
      crc ^= poly; //Xor CRC-Poly
    }
    //next data Bit
    data >>= 1;
  }
  return crc;
}

//------------------------------------------------------------

/**
 * Alternate Algo 1
   Load the register with zero bits.
   Augment the message by appending W zero bits to the end of it.
   While (more message bits)
      Begin
      Shift the register left by one bit, reading the next bit of the
         augmented message into register bit position 0.
      If (a 1 bit popped out of the register during step 3)
         Register = Register XOR Poly.
      End
   The register now contains the remainder.
 */
u16 CRCCalc::alt01(u8 data){
  u16 reg = 0;
  u16 tmp;
  for(int ii=0; ii<8; ++ii){
    tmp = reg & 0x1000u;
    reg <<= 1U;
    reg = (data & 0x0001u) | (reg & 0xFFFEu);
    if(tmp>0){
      reg ^= poly;
    }
  }
  return reg;
}

//------------------------------------------------------------

/**
 *
 */
vector<u8> CRCCalc::addcrc(vector<u8> v, u16 p, u16 i){
  CRCCalc cc;
  cc.setpoly(p);
  cc.init(i);
  u16 lcrc = Utility::Bittwiddle::byteswap(Algorithms::Bitreverse::simple_method<u16>(~cc.doblock(v)));
  v.push_back((u8)(lcrc & 0x00FFu));
  v.push_back((u8)((lcrc>>8) & 0x00FFu));
  return v;
}

/**
 *
 */
u16 CRCCalc::checkinvert(void){
  u16 bkup = crc;
  union s2b{
    u16 s;
    u8 b[2];
  };
  union s2b tmp;
  tmp.s = ~crc;
  dobyte(tmp.b[0]);
  tmp.s = dobyte(tmp.b[1]);
  crc = bkup;
  return tmp.s;
}

//------------------------------------------------------------

}

