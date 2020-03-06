/******************************************************************************/
/** Compact Datatype Definitions                                             **/
/** collected and / or implemented by                                        **/
/** Danny Schneider, 2017-2020                                               **/
/******************************************************************************/

/*
 * Copyright (c) 2020, Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. (of course you are
 * allowed to extend the above copyright notice by the means of adding your
 * name and date if and only if you have contributed to the source)
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Redistributions of any forked and or modified version of this code in binary
 * form need to make the source code availible upon request. If maintainance of any
 * forked and or modified version of this code is stopped, future access to the code
 * needs to be ensured e.g. by at least uploading it to an public open platform and
 * or the official original repository if availible.
 *
 * 4. Usage of this code (stating Discrimination Against Fields of Endeavor [*1] )
 * neither in source nor in binary form - in any military, intelligence,
 * public surveillance, surveillance state , political supression context is forbidden
 * Simply:
 * do not use this software to harm people or to violate non-derogable human rights
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
 *
 * [*1]: Comment of Conndition 4, yes this conndition violates the Open Source Definition
 * But as an Engineer with a german background I do believe you are responsible how the
 * things are used you develop. So yes, even if Conndition 4 might be circumvented and/or
 * be ignored by bad people, I want to state with this liecense, that my intend is to not
 * have the software used to harm people, and I want to ask you to respect this.
 */

#ifndef ITERATORS_H
#define ITERATORS_H

#include "compile_guards.h"

namespace Core {

namespace Container {

template<typename T> using  iterator_t = T*;
template<typename T> using citerator_t = T const *;

//-----

template<typename T> citerator_t<T> constify(iterator_t<T> it){
  return reinterpret_cast<citerator_t<T>>(it);
}

//-----

template<typename T> bool is_valid(citerator_t<T> cit){
  return (nullptr != cit);
}
template<typename T> bool is_valid(iterator_t<T> it){
  return is_valid<T>(constify<T>(it));
}

//-----

template<typename T, typename I> bool set_at(iterator_t<T> it, I offset, T const& data){
  Compile::Guards::IsUnsigned<I>();
  bool res = is_valid<T>(it);
  if(res){
    it[offset] = data;
  }
  return res;
}

//-----

template<typename T, typename I> T get_at(citerator_t<T> cit, I offset){
  Compile::Guards::IsUnsigned<I>();
  T res{};
  if(is_valid<T>(cit)){
    res = cit[offset];
  }
  return res;
}

template<typename T, typename I> T get_at(iterator_t<T> it, I offset){
  Compile::Guards::IsUnsigned<I>();
  return get_at<T,I>(constify<T>(it),offset);
}

//-----

template<typename T, typename I> citerator_t<T> advance(citerator_t<T> cit, I offset){
  Compile::Guards::IsUnsigned<I>();
  return &cit[offset];
}

template<typename T, typename I> iterator_t<T> advance(iterator_t<T> it, I offset){
  Compile::Guards::IsUnsigned<I>();
  return &it[offset];
}

//-----

} //namespace

} //namespace

#endif // ITERATORS_H
