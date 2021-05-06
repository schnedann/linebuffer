#include <iterator>
#include <algorithm>

#include "global_config.h"
#include "debug_hlp.h"
#include "large_mul.h"

#ifdef DEBUG_CODE
  #include "debug_hlp.h"
#endif

using namespace std;

#ifdef DEBUG_CODE
template<class T> string prnvector(T const& in, u16 const cols, u8 const width, bool const in_hex=true, bool const no_final_linebreak=true){
  size_t col=1;
  stringstream ss;

  auto cnt = in.size();
  if(cnt>0){
    cnt-=1;

    for(auto x:in){
      if(in_hex){
        ss << "0x" << setw(width) << setfill('0') << hex << (u64)x << "u";
      }else{
        ss << setw(width) << setfill(' ') << dec << (u64)x << "u";
      }

      bool const next_row = ((col%cols)==0);
      bool const add_final = !(no_final_linebreak && (cnt==0));
      if(next_row && add_final){
        ss << ",\n";
      }
      if(!next_row){
        ss << ", ";
      }
      ++col;
      --cnt;
    }
    ss << dec;
    bool const row_complete = ((col%cols)==0);
    bool const add_final = !no_final_linebreak;
    if(!row_complete && add_final){ss << "\n";}
  }
  return ss.str();
}
#endif

//-----

/*
 * Serialize Integer Type to ByteVector
 */
template<class T> std::vector<u8> serialize(T const& x){
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
template<class T> T deserialize(std::vector<u8> const& x){
  T deserialized = 0;
  u8 shift = 0;
  for(std::vector<u8>::const_iterator it=x.begin(); it!=x.end(); ++it){
    deserialized |= ((*it)<<(shift<<3));
    ++shift;
  }
  return deserialized;
}

//-----

/**
 *
 */
std::vector<u8> Math::Large_Mul::multiply(std::vector<u8> const& pa, std::vector<u8> const& pb){

  DBGPUT(__PRETTY_FUNCTION__)

  DBGPUT(Utility::Strings::stradd<2>({"Input pa:\n",prnvector(pa,8,Math::Boolean::GETNIBBLESOFTYPE<u8>())}))
  DBGPUT(Utility::Strings::stradd<2>({"Input pb:\n",prnvector(pb,8,Math::Boolean::GETNIBBLESOFTYPE<u8>())}))

  vector<u8> result(pa.size()+pb.size(),0);
  vector<u8> intermidiate(pa.size()*pb.size(),0);

  using idx_t = decltype(intermidiate.size());

  constexpr auto const mask02 = Math::Boolean::GETMASKBIT<idx_t>(1);
  constexpr auto const mask04 = Math::Boolean::GETMASKBIT<idx_t>(2);
  constexpr auto const mask08 = Math::Boolean::GETMASKBIT<idx_t>(3);
  constexpr auto const mask16 = Math::Boolean::GETMASKBIT<idx_t>(4);
  constexpr auto const mask32 = Math::Boolean::GETMASKBIT<idx_t>(5);
  constexpr auto const mask64 = Math::Boolean::GETMASKBIT<idx_t>(6);

  for(idx_t mply_cnt=0; mply_cnt<intermidiate.size() ; ++mply_cnt){
    idx_t base_idx1 = (Math::Boolean::IS_ODD(mply_cnt))?(1):(0);
    idx_t base_idx2 = (Math::Boolean::AND(mply_cnt,mask02)>0)?(1):(0);
    idx_t cycle04 = (Math::Boolean::AND(mply_cnt,mask04)>0)?(1):(0);
    idx_t cycle08 = (Math::Boolean::AND(mply_cnt,mask08)>0)?(1):(0);
    idx_t cycle16 = (Math::Boolean::AND(mply_cnt,mask16)>0)?(1):(0);
    idx_t cycle32 = (Math::Boolean::AND(mply_cnt,mask32)>0)?(1):(0);
    idx_t cycle64 = (Math::Boolean::AND(mply_cnt,mask64)>0)?(1):(0);

    idx_t idx1 = base_idx1 + 2*cycle04;
    idx_t idx2 = base_idx2 + 2*cycle08;

    intermidiate[mply_cnt] = pa[idx1] * pb[idx2];
  }

  return result;
}

/*
 * Multiply unsigned 16Bit * unsigned 16Bit = unsigned 32Bit
 */
u32 Math::Large_Mul::mulu16(u16 const& _a,u16 const& _b){
  std::vector<u8> pa = serialize<u16>(_a);
  std::vector<u8> pb = serialize<u16>(_b);

  std::vector<u8> result = multiply(pa,pb);

  u32 ret = deserialize<u32>(result);
  return ret;
}

/*
 * Multiply unsigned 32Bit * unsigned 32Bit = unsigned 64Bit
 */
u64 Math::Large_Mul::mulu32(u32 const& _a,u32 const& _b){

  std::vector<u8> pa = serialize<u32>(_a);
  std::vector<u8> pb = serialize<u32>(_b);

  std::vector<u8> result = multiply(pa,pb);

  u64 ret = deserialize<u64>(result);
  return ret;
}

/*
 * Multiply unsigned 64Bit * unsigned 64Bit = unsigned 128Bit
 */
Math::Large_Mul::u128 Math::Large_Mul::mulu64(u64 const& _a,u64 const& _b){

  std::vector<u8> pa = serialize<u64>(_a);
  std::vector<u8> pb = serialize<u64>(_b);

  std::vector<u8> result = multiply(pa,pb);

  u128 ret;
  ret.d[0] = deserialize<u64>(std::vector<u8>(result.begin(),result.begin()+(sizeof(u64)-1)));
  ret.d[1] = deserialize<u64>(std::vector<u8>(result.begin()+sizeof(u64),result.begin()+((sizeof(u64)<<1)-1)));
  return ret;
}
