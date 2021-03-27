#include "bitcalc.h"

size_t bitcalc::bits_to_bytes(size_t const bits){
  return (bits>>3)+(((bits%2)>0)?(1):(0));
}
