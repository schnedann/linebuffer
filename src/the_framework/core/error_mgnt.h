#ifndef ERROR_MGNT_H
#define ERROR_MGNT_H

#include <string>
#include <utility>
#include <functional>

#include "dtypes.h"

namespace Core {

namespace Flow {

template<typename T> using with_error_t = std::pair<bool,T>;

template<typename T> [[nodiscard]] bool has_error(with_error_t<T> const& we){
  return we.first;
}

template<typename T> [[nodiscard]] T& get_value(with_error_t<T>& we){
  return we.second;
}

template<typename T> [[nodiscard]] T const& get_value(with_error_t<T> const& we){
  return we.second;
}

template<typename T> [[nodiscard]] with_error_t<T> make_with_error(T const& _v, bool const err=false){
  return std::make_pair(err,_v);
}

void if_no_err(std::function<bool()> const& exec, std::function<void()> const& errhdlr, bool& err);
void if_no_err(std::function<bool(std::string&)> const& exec, std::function<void(std::string const&)> const& errhdlr, bool& err);

template<typename T> void set_error(with_error_t<T>& we, bool const err){
  we.first = err;
  return;
}

template<typename T> void set_value(with_error_t<T>& we, T const& _v){
  return we.second = _v;
}

} //namespace

} //namespace


#endif // ERROR_MGNT_H
