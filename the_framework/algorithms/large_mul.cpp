#include <iterator>
#include <algorithm>

#include "large_mul.h"

#ifdef DEBUG
  #include <iostream>
  #include <iomanip>
  #include <string>
  #include <sstream>
#endif

using namespace std;

#ifdef DEBUG
template<class T> string prnvector(T const& in,u16 const& cols, u8 const& width, bool const& in_hex){
  size_t ii=1;
  stringstream ss;

  for(auto x:in){

    if(in_hex){
      ss << "0x" << setw(width) << setfill('0') << hex << (u64)x << "u";
    }else{
      ss << setw(width) << setfill(' ') << dec << (u64)x << "u";
    }

    if((ii%cols)==0){
      ss << endl;
    }else{
      ss << " , ";
    }
    ++ii;
  }
  ss << dec << endl;
  return ss.str();
}
#endif

//-----

/*
 * Serialize Integer Type to ByteVector
 */
template<class T> auto serialize(T const& x)->std::vector<u8>{
  std::vector<u8> serialized(sizeof(T),0);
  T y = x;
  T const mask = (T)0xFFu;
  for(std::vector<u8>::iterator it=serialized.begin(); it!=serialized.end(); ++it){
    *it = y&mask;
    y>>=8;
  }
  return serialized;
}

/*
 * Deserialize a Byte Vector to Integer Type
 */
template<class T> auto deserialize(std::vector<u8> const& x)->T{
  T deserialized = 0;
  u8 shift = 0;
  for(std::vector<u8>::const_iterator it=x.begin(); it!=x.end(); ++it){
    deserialized |= ((*it)<<(shift<<3));
    ++shift;
  }
  return deserialized;
}

//-----

/*
 *
 */
auto Math::Large_Mul::multiply(std::vector<u8> const& pa, std::vector<u8> const& pb) -> std::vector<u8>
{
#ifdef DEBUG
  cout << "Input pa:" << endl << prnvector(pa,8,sizeof(u8)>>2,true);
  cout << "Input pb:" << endl << prnvector(pb,8,sizeof(u8)>>2,true);
#endif

  vector<u8>  result(pa.size()+pb.size(),0);
  vector<u16> intermidiate(pa.size()*pb.size(),0);
  vector<u8>  shiftcnt(pa.size()*pb.size(),0);

  /*
   * Multply atoms
   */
  vector<u8>::const_iterator ait=pa.begin();
  vector<u8>::const_iterator bit=pb.begin();
  u8 cnt_a = 1;
  u8 cnt_b = 1;
  for(vector<u16>::iterator iit=intermidiate.begin(); iit!=intermidiate.end(); ++iit){
    //----- Multiply
    *iit=(u16)(*ait) * (u16)(*bit);
    //----- Shift Count Values
    vector<u8>::iterator shit = shiftcnt.begin();
    std::advance(shit,std::distance(intermidiate.begin(),iit));
    *shit = cnt_a * cnt_b;
    //----- Index Manipulations
    ++ait;
    ++cnt_a;
    if(ait==pa.end()){
      ait=pa.begin();
      cnt_a = 1;
      ++bit;
      ++cnt_b;
    }
    //-----
  }
#ifdef DEBUG
  cout << "Piecewise Multiplication" << endl << prnvector(intermidiate,2,sizeof(u16)>>2,true);
#endif

  /*
   * Rescale Shift Count Values
   */
  for(vector<u8>::iterator shit=shiftcnt.begin(); shit!=shiftcnt.end(); ++shit){
    *shit = ((*shit)>>1);
  }
#ifdef DEBUG
  cout << "Shift Counts" << endl << prnvector(shiftcnt,2,sizeof(u8)>>2,true);
#endif

  /*
   * Assemble Result
   * scv -> Shift Count current value
   */
  u8 index = 0;
  vector<u8>::const_iterator shit=shiftcnt.begin();
  u8 scv_previous = *shit;
  for(vector<u16>::const_iterator iit=intermidiate.begin(); iit!=intermidiate.end(); ++iit){
    u8 const scv = *shit;
    if(scv!=scv_previous){
      ++index;
      scv_previous = scv;
    }

    //Lower 8-Bit
    u8 carry = 0;
    {
      u8 num2 = (u8) ((*iit)&0x00FFu);
      //Check for Overflow
      if((num2&0x80u)&(result[index]&0x80u)){
        //Overflow
        carry += 1;
      }else{
        //No Overflow
      }

#ifdef DEBUG
  cout << (u16)result[index] << " + " << (u16)num2 ;
#endif
      result[index] += num2;
#ifdef DEBUG
  cout << " = " << (u16)result[index] << endl;
#endif
    }

#ifdef DEBUG
  cout << "A-Carry: " << (u16)carry << endl;
#endif

    //Higher 8-Bit
    {
      u8 num2 = (u8)(((*iit)&0xFF00u)>>8);
      //Check for Overflow
      if((num2&0x80u)&(result[index]&0x80u)){
        //Overflow
        carry += 1;
      }else{
        //No Overflow
      }

#ifdef DEBUG
  cout << (u16)result[index+1] << " + " << (u16)num2 ;
#endif
      result[index+1] += num2;
#ifdef DEBUG
  cout << " = " << (u16)result[index+1] << endl;
#endif
    }

#ifdef DEBUG
  cout << "B-Carry: " << (u16)carry << endl;
#endif

    //Handle Carry Bits
    while(carry>0){
      u8 num2 = carry;
      //Check for Overflow
      if((num2&0x80u)&(result[index]&0x80u)){
        //Overflow
        carry = 1;
      }else{
        //No Overflow
        carry = 0;
      }
      result[index+1] += num2;
#ifdef DEBUG
  cout << "C-Carry: " << (u16)carry << endl;
#endif
    }

#ifdef DEBUG
  cout << "Index: " << (u16)index << endl;
  cout << prnvector(result,2,sizeof(u8)>>2,true);
#endif

    ++shit;
  }

  return result;
}

/*
 * Multiply unsigned 16Bit * unsigned 16Bit = unsigned 32Bit
 */
auto Math::Large_Mul::mulu16(u16 const& _a,u16 const& _b) -> u32{
  std::vector<u8> pa = serialize<u16>(_a);
  std::vector<u8> pb = serialize<u16>(_b);

  std::vector<u8> result = multiply(pa,pb);

  u32 ret = deserialize<u32>(result);
  return ret;
}

/*
 * Multiply unsigned 32Bit * unsigned 32Bit = unsigned 64Bit
 */
auto Math::Large_Mul::mulu32(u32 const& _a,u32 const& _b) -> u64{

  std::vector<u8> pa = serialize<u32>(_a);
  std::vector<u8> pb = serialize<u32>(_b);

  std::vector<u8> result = multiply(pa,pb);

  u64 ret = deserialize<u64>(result);
  return ret;
}

/*
 * Multiply unsigned 64Bit * unsigned 64Bit = unsigned 128Bit
 */
auto Math::Large_Mul::mulu64(u64 const& _a,u64 const& _b) -> u128{

  std::vector<u8> pa = serialize<u64>(_a);
  std::vector<u8> pb = serialize<u64>(_b);

  std::vector<u8> result = multiply(pa,pb);

  u128 ret;
  ret.d[0] = deserialize<u64>(std::vector<u8>(result.begin(),result.begin()+(sizeof(u64)-1)));
  ret.d[1] = deserialize<u64>(std::vector<u8>(result.begin()+sizeof(u64),result.begin()+((sizeof(u64)<<1)-1)));
  return ret;
}
