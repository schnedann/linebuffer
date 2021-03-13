/******************************************************************************/
/**                                                                          **/
/** implemented by                                                           **/
/** Danny Schneider, 2018-2021                                               **/
/******************************************************************************/

/*
 * Copyright 2018-2021, Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation and/or
 * other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef ARRAY_FUN_H
#define ARRAY_FUN_H

#include "dtypes.h"
#include "iterators.h"

namespace Core {

namespace Array {

/**
 * @brief Fill Array with constant value
 */
template<typename T, size_t N> constexpr void fill(T (&_a)[N], T const& fill){
  for(size_t ii=0; ii<N; ++ii){
    _a[ii] = fill;
  }
  return;
}

/**
 * @brief Fill Array with constant value
 */
template<typename T, typename I> void fill_ptr(Core::Container::iterator_t<T> ptr, I const count, T const& fill){
  for(size_t ii=0; ii<count; ++ii){
    ptr[ii] = fill;
  }
  return;
}

/**
 * @brief Fast Copy of Array from source to target,
 * @note  Choose CT to be the largest system Integer supported by the target architecture
 */
template<typename T, typename CT, typename I> void copy_ptr(Core::Container::citerator_t<T> sptr,
                                                               Core::Container::iterator_t<T> tptr,
                                                               I const count){
  constexpr size_t bytesT   = sizeof(T);
  constexpr size_t bytesCT  = sizeof(CT);
  size_t bytes_s  = count * bytesT;
  size_t cntCT    = bytes_s / bytesCT;
  size_t bytes_fastcopy = (cntCT * bytesCT);
  size_t cnt_rest = bytes_s - bytes_fastcopy;

  //Mass Copy
  auto sptr_CT = reinterpret_cast<Core::Container::citerator_t<CT>>(sptr);
  auto tptr_CT = reinterpret_cast<Core::Container::iterator_t<CT>>(tptr);
  for(size_t ii=0; ii<cntCT; ++ii){
    tptr_CT[ii] = sptr_CT[ii];
  }

  //Copy bytes left
  size_t offset = bytes_fastcopy;
  auto sptr_byte = reinterpret_cast<Core::Container::citerator_t<u8>>(sptr);
  auto tptr_byte = reinterpret_cast<Core::Container::iterator_t<u8>>(tptr);
  for(size_t ii=0; ii<cnt_rest; ++ii){
    tptr_byte[ii+offset] = sptr_byte[ii+offset];
  }
  return;
}

/**
 * @brief
 */
template<typename T, typename CT, size_t N> constexpr void copy(T const (&_s)[N], T (&_t)[N]){
  copymem_ptr<T,CT,size_t>(&_s[0],&_t[0],N);
  return;
}

/**
 * @brief  Compare two Arrays
 * @return true if content is equal
 */
template<typename T, size_t N> bool cmp(T const (&_a)[N], T const (&_b)[N]){
  bool res = true;
  for(size_t  ii=0; ii<N; ++ii){
    res &= (_a[ii]==_b[ii]);
    if(!res){
      break;
    }
  }
  return res;
}

/**
 * @brief  Compare two Arrays
 * @return true if content is equal
 */
template<typename T, typename I> bool cmp_ptr(Core::Container::citerator_t<T> aptr,
                                                   Core::Container::citerator_t<T> bptr,
                                                   I const count){
  bool res = true;
  for(I  ii=0; ii<count; ++ii){
    res &= (aptr[ii]==bptr[ii]);
    if(!res){
      break;
    }
  }
  return res;
}

} //namespace

} //namespace

#endif // ARRAY_FUN_H
