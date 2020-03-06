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
