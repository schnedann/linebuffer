#include "minilog2.h"

/**
 * Equals floor(log2(_x))
 */
u8 Algorithms::Log2::minilog2(u8 const _x){
  constexpr static u8 const c4 = 0xF0U; // 11110000
  constexpr static u8 const c3 = 0xCU;  // 00001100
  constexpr static u8 const c2 = 0x02U; // 00000010

  u8 dut = _x;
  u8 res = 0;
  //Bit in highest Nibble?
  if((dut&c4)>0){
    res += 4;  //must be >= 4
    dut >>= 4; //Throw away lower bits
  }
  //Bit in upper 2 Bits of nibble
  if((dut&c3)>0){
    res += 2;  //must be >= 2
    dut >>= 2; //Throw away lower bits
  }
  if((dut&c2)>0){
    res += 1;  //must be >= 1
  }
  return res;
}
