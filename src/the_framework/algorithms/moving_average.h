#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <array>

#include "dtypes.h"
#include "fifo_fixed_size.h"
#include "math_discrete.h"
#include "ovf_save.h"

namespace Algorithms {

template<typename T, size_t N> class moving_average{
private:
  T cma{0};
  T sma{0};
  Datastructures::fifo_fixed_size<T,N> ffs;

  /**
   * @brief cumulative
   * @param value
   * @return
   */
  T cumulative(T const& value){
    cma = cma + Math::Discrete::udivround<T>((value-value),2);
    return cma;
  }

  /**
   * @brief simple
   * @param value
   * @return
   */
  T simple(T const& value){
    ffs.put(value);

    sma = 0;
    for(auto const& _v:ffs.buffer()){
      sma = sma + Math::Discrete::udivround<T>(Math::OverflowSafe::satt_usub<T>(_v,sma),2);
    }
    return sma;
  }
public:
  moving_average():cma(T()),sma(0){}

  /**
   * @brief put - add data to filter
   * @param _x
   */
  void put(T const& _x){
    static_cast<void>(cumulative(_x));
    static_cast<void>(simple(_x));
    return;
  }

  std::array<T,N> const& buffer() const{
    return ffs.buffer();
  }

  T get_c() const{
    return cma;
  }

  T get_s() const{
    return sma;
  }
};

} //namespace

#endif // MOVING_AVERAGE_H
