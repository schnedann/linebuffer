#include <iostream>
#include <iomanip>

#include "crcalgo.h"
#include "../bitlib/bitmacros.h"
#include "../bitlib/bitlib.h"
#include "../bitlib/bitcalc.h"

using namespace std;

crc_algo_para_t std_crc_algo[]={
{        8,
        32,
      true,
      true,
     false,
0x04C11DB7u,
0xFFFFFFFFu,
0xFFFFFFFFu},
{        8,
         8,
     false,
     false,
     false,
     0x07u,
     0x00u,
     0x00u},
{        8,
         8,
     false,
     false,
     false,
     0x9Bu,
     0xFFu,
     0x00u},
{        8,
         8,
     false,
     false,
     false,
     0xD5u,
     0x00u,
     0x00u}
};

crcalgo::crcalgo()
{
}

crcalgo::~crcalgo()
{
}

/**
 *
 */
void crcalgo::setpara(crc_algo_para_t cap){
  para = cap;
  return;
}

/**
 *
 */
u8 crcalgo::dbytes(){
  return bitcalc().bits_to_bytes<u8>(para.dwidth);
  //return (para.dwidth>>3)+(((para.dwidth%2)>0)?(1):(0));
}

/**
 *
 */
u8 crcalgo::pbytes(){
  return bitcalc().bits_to_bytes<u8>(para.pwidth);
  //return (para.pwidth>>3)+(((para.pwidth%2)>0)?(1):(0));
}

/**
 *
 */
u8 crcalgo::dbits(){
  return para.dwidth;
}

/**
 *
 */
u8 crcalgo::pbits(){
  return para.pwidth;
}

/**
 *
 */
u64 crcalgo::poly(){
  return para.poly;
}

/**
 *
 */
u64 crcalgo::init(){
  return para.init;
}

/**
 * Final Reflect / XOR
 */
u64 crcalgo::getresult(u64 const& crc_reg){
  u64 crc;
  if(para.ref_result==true){
    crc = bitrev32(crc_reg);
    maSHR(crc,(32-para.pwidth));
  }else{
    crc = crc_reg;
  }
  maXOR(crc,para.fxor); //XOR with fixed Value => set to zero to turn off
  return crc;
}

/**
 * Single Bit Step
 */
u64 crcalgo::serial_step(bool const& data, u64 const& init){
  u64 poly;
  u64 crc = init;

  //Reflect Poly --> Bitreverse
  if(para.ref_poly==true){
    poly = bitrev32(para.poly);
    maSHR(poly,(32-para.pwidth));
  }else{
    poly = para.poly;
  }

  //Blend in Data
  maXOR(crc,((data==true)?(1):(0)));

  if(mAND(crc,(1U<<para.pwidth))>0){
    //shift CRC
    maSHL(crc,1,0);
    //Divide with Poly
    maXOR(crc,poly);
  }else{
    //shift CRC
    maSHL(crc,1,0);
  }

  u64 const mask = mBitMask(para.pwidth);
  maAND(crc,mask); //Limit to X-bit

  return crc;
}

/**
 * X Bit "parallel" Algorithm
 */
u64 crcalgo::calc(u64 const& data, u64 const& init){
  u64 poly;
  u64 crc = init;

  //Reflect Poly --> Bitreverse
  if(para.ref_poly==true){
    poly = bitrev32(para.poly);
    maSHR(poly,(32-para.pwidth));
  }else{
    poly = para.poly;
  }

  //Data must be shifted or
  //or bitreversed + shifted
  u64 tmp1;
  if(para.ref_data==true){
    tmp1 = bitrev32(data);
    maSHR(tmp1,(32-para.pwidth));
  }else{
    tmp1 = data;
    maSHL(tmp1,para.pwidth-para.dwidth,0);
  }

  //Blend Data + CRC Register
  maXOR(crc,tmp1);

  for(int ii=0;ii<para.dwidth;++ii){
    //Fetch CRC Bit
    u64 rem=(mGetBit(crc,(para.pwidth-1))>0)?(1):(0);

    //shift CRC
    maSHL(crc,1,0);

    //Divide with Poly
    if(rem>0){
      maXOR(crc,poly);
    }
  }

  u64 const mask = mBitMask(para.pwidth);
  maAND(crc,mask); //Limit to X-bit

  return crc;
}

/**
 * calc crc with algo-parameters of the series: 
 * {0,1,2,3,4,5,6,7,8,9}
 * and compare with known result
 */
bool crcalgo::check(u64 const& _check){
  bool res = false;

  char const data[] = "123456789";

  cout << "Checking: " << endl <<
  ",CRC    : " << dec << (int)para.pwidth << endl <<
  ",Data   : " << dec << (int)para.dwidth << endl <<
  ",Poly   : 0x" << hex << para.poly << endl <<
  ",Init   : 0x" << hex << para.init << endl <<
  ",Ref_in : " << dec << para.ref_data << endl <<
  ",Ref_out: " << dec << para.ref_result << endl <<
  ",Fin_XOR: 0x" << hex << para.fxor << endl;

  u64 crcreg = para.init;
  u64 crcres;
  for(u64 ii=0; ii<9; ++ii){
    crcreg = calc(data[ii],crcreg);
    crcres = getresult(crcreg);
    cout << ii << ": " << hex << (int)data[ii] << " -> " << "0x" << setw(8) << setfill('0') << hex << crcres << endl;
  }

  if(crcres==_check){
    res=true;
    cout << "Check passed successfully..." << endl;
  }else{
    cout << "Check failed..." << endl;
  }

  return res;
}
