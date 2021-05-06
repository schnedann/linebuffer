#include <ctime>
#include <cstdlib>

#include "bitmacros.h"
#include "gendata.h"

/**
 * Generate Linear Dataset
 * start = 1st Value+
 * step  = spacing
 * end   = max. possible value
 */
std::vector<u8> genlinear(u32 const start, u32 const step, u32 const end){
  std::vector<u8> res;
  if(end>start){
    auto index = start;
    if((index+step)<=end){
      while(index<=end){
        res.push_back(index);
        index += step;
      }
    }
  }
  return res;
}

/**
 * Generate Random Dataset
 * length = Number of Samples
 */
std::vector<u8> genrand(u32 const length){
  std::vector<u8> res(length);

  srand(time(NULL)); //initialize random seed

  for(u32 ii=0; ii<length; ++ii){
    res.push_back((u8)(rand() % 256));
  }
  return res;
}
