#ifndef UTILITY_GENDATA_H
#define GENDATA_H

#include <vector>

#include "dtypes.h"

namespace Utility{

namespace GenData {

  std::vector<unsigned char> genlinear(u32 const start, u32 const step, u32 const end);
  std::vector<unsigned char> genrand(u32);

} //namespace

} //namespace

#endif // GENDATA_H
