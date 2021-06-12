#include <ctime>
#include <cstdlib>
#include <random>

#include "bitmacros.h"
#include "gendata.h"

/**
 * Generate Linear Dataset
 * start = 1st Value+
 * step  = spacing
 * end   = max. possible value
 */
std::vector<u8> Utility::GenData::genlinear(u32 const start, u32 const step, u32 const end){
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
std::vector<u8> Utility::GenData::genrand(u32 const length){
  std::random_device rd;  //Will be used to obtain a seed for the random number engine
  std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
  std::uniform_int_distribution<u8> distrib(0, 255);

  std::vector<u8> res(length);

  for(auto& _x:res){
    _x = distrib(gen);
  }
  return res;
}
