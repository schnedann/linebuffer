/**
 * Danny Schneider, 2017
 *
 * Mechanism for doing almost infinite long integer Multiplications
 * Implementation is more suited for smaller length like doing 32 + 64
 * Bit Operations on 8 or 16 Bit devices...
 */

#ifndef _LARGE_MUL_H_
#define _LARGE_MUL_H_

//#include <array>
#include <vector>

#include "dtypes.h"

//#define DEBUG

namespace Math{

namespace Large_Mul{

//Integer Type for everything > u64
template<typename T, u64 cnt> class ux_t{
  public:
  T d[cnt];
};

using u128 = ux_t<u64,2>; //Define 128Bit Type

//General Purpose Multiply
auto multiply(std::vector<u8> const& _a, std::vector<u8> const& _b) -> std::vector<u8>;

//Specialized Multiply Implementations
auto mulu16(u16 const& _a,u16 const& _b) -> u32;
auto mulu32(u32 const& _a,u32 const& _b) -> u64;
auto mulu64(u64 const& _a,u64 const& _b) -> u128;

} //Namespace

} //Namespace

#endif // _LARGE_MUL_H_
