/**
 * Danny Schneider, 2017
 *
 * Mechanism for doing almost infinite long integer Multiplications
 * Implementation is more suited for smaller length like doing 32 + 64
 * Bit Operations on 8 or 16 Bit devices...
 */

#ifndef _LARGE_MUL_H_
#define _LARGE_MUL_H_

#include <vector>

#include "dtypes.h"

namespace Math{

namespace Large_Mul{

//Integer Type for everything > u64
template<typename T, u64 cnt> class ux_t{
  public:
  T d[cnt];
};

using u128 = ux_t<u64,2>; //Define 128Bit Type

//General Purpose Multiply
std::vector<u8> multiply(std::vector<u8> const& _a, std::vector<u8> const& _b);

//Specialized Multiply Implementations
u32 mulu16(u16 const& _a,u16 const& _b);
u64 mulu32(u32 const& _a,u32 const& _b);
u128 mulu64(u64 const& _a,u64 const& _b);

} //Namespace

} //Namespace

#endif // _LARGE_MUL_H_
