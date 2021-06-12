#include <iostream>
#include <iomanip>
#include <iterator>

#include "hdlgenerate.h"

#define mSetBit(_v,b)  (_v|=(1U<<b))
#define mGetBit(_v,b)  (_v&(1U<<b))
#define mClrBit(_v,b)  (_v&=~(1U<<b))
#define mSHL(_v,b)     (_v<<=b)
#define mSHR(_v,b)     (_v>>=b)
#define mXOR(x,y)      (x^=y)
#define mCNTUP(_v,max) (_v=((_v+1)%max))

using namespace std;

string Application::hdlgenerate::poly2str(){
  //string res;
  u8 ij = crcwidth-1;
  stringstream ss;
  for(int ii=(1U<<(crcwidth-1));ii>0;ii>>=1){
    if(poly & ii){
      ss << "x^" << (int)ij--;
      if(ii>1) ss << "+";
    }
  }
  return ss.str();
}

string Application::hdlgenerate::genhdl(u16 poly){
  string res;
  u16 tmp;
  u16 test;
  u16 crc = 0xFFFFu;
  u8 dbit = 0;
  u8 cbit = 0;
  u8 maxcycle = 0;

//-----
initgen();
//-----
setdbits(8);
setcbits(16);
setpoly(0xc86cu);
setival(0xFFFFu);
//-----
  do{
    //MSB Set or Cleared?
    tmp = (mGetBit(crc,15)>0)?(1):(0);
    //shift out MSB + shift in a zero
    mSHL(crc,1);
    mClrBit(crc,0);

    mCNTUP(cbit,16);
    //if MSB was Set
    if(tmp > 0){
for(int ii=0; ii<16; ++ii){
  if((crc&(1U<<ii))>0){
    cout << "Bit: " << (ii - 1) << endl;
    mSetBit(test,ii);
  }
}
      mXOR(crc,poly);
    }
    mCNTUP(dbit,8);
    ++maxcycle;
  }while(maxcycle<200);
  cout << "Test: " << test << endl;
  return res;
}

/**
 * Init Vector of Strings
 */
void Application::hdlgenerate::initgen(void){
  while(hdlcode.size()<16){
    hdlcode.push_back(std::string());
  }
  cout << "Vector has Size: " << dec << hdlcode.size() << endl;
  const string str = "";
  for(vector<string>::iterator it = hdlcode.begin(); it!=hdlcode.end();++it){
    *it = str;
  }
  return;
}

void Application::hdlgenerate::setdbits(u32 const _v){
  dbits = _v;
}

void Application::hdlgenerate::setcbits(u32 const _v){
  cbits = _v;
}

void Application::hdlgenerate::setpoly(u32 const _v){
  poly = _v;
}

void Application::hdlgenerate::setival(u32 const _v){
  ival = _v;
}
