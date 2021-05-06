#include <array>
#include "utility_fct.h"

/**
 *
 */
u16 Utility::Bittwiddle::byteswap(u16 val){
  union bsw_u{
    u16 s;
    std::array<u8,2> b{};
  } bsw;
  bsw.s = val;
  unsigned char tmp = bsw.b[0];
  bsw.b[0] = bsw.b[1];
  bsw.b[1] = tmp;
  return bsw.s;
}
