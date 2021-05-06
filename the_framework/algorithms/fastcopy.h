#ifndef FASTCOPY_H
#define FASTCOPY_H

#include "dtypes.h"
#include "iterators.h"

namespace Algorithms {

using block_t = unsigned int;

/**
 * @brief fastcopy - Copy Data of Type T from Source Array to Target Array
 * @param sptr - Source Pointer
 * @param tptr - Target Pointer
 * @param elements - Number of Elements of Type T
 */
template<typename T> void fastcopy(Core::Container::citerator_t<T> sptr,
                                   Core::Container::iterator_t<T>  tptr,
                                   size_t elements){

  size_t bytes = sizeof(T)*elements;
  size_t blocks = bytes/sizeof(block_t);            //efficient copyable blocks
  size_t offset = blocks*sizeof(block_t);
  size_t rbytes = bytes - offset; //remaining bytes

  //Copy all blocks of type block_t
  auto blksptr = reinterpret_cast<Core::Container::citerator_t<block_t>>(sptr);
  auto blktptr = reinterpret_cast<Core::Container::iterator_t<block_t>>(tptr);
  for(size_t idx=0; idx<blocks; ++idx){
    blktptr[idx] = blksptr[idx];
  }

  //Copy remaining bytes
  auto bsptr = reinterpret_cast<Core::Container::citerator_t<u8>>(sptr);
  auto btptr = &(reinterpret_cast<Core::Container::iterator_t<u8>>(tptr)[offset]);
  for(size_t idx=0; idx<rbytes; ++idx){
    btptr[idx] = bsptr[idx];
  }
  return;
}

} //namespace

#endif
