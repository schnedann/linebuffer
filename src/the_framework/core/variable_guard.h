#ifndef VARIABLE_GUARD_H
#define VARIABLE_GUARD_H

#include "dtypes.h"
#include "iterators.h"

namespace Core {

namespace RuntimeGuards {

/**
 * @brief class variable_guard - on instanciation it stores a variable by pointer-access,
 *                               and restores this value at destruction
 */
template<typename T> class variable_guard{
private:
  T orig{};                                        //Store Original Value
  Core::Container::iterator_t<T> origptr{nullptr}; //Store Pointer to Variable
public:
  explicit variable_guard(Core::Container::iterator_t<T> it):orig(Core::Container::get_at<T,size_t>(it,0)),origptr(it){}
  variable_guard(variable_guard const&)=delete;
  variable_guard(variable_guard&&)=delete;
  ~variable_guard(){
    static_cast<void>(Core::Container::set_at<T,size_t>(origptr,0,orig));
    return;
  }
  T get(){
    return orig;
  }
};

} //namespace

} //namespace


#endif // VARIABLE_GUARD_H
