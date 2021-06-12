#ifndef MEDIAN_FILTER_H
#define MEDIAN_FILTER_H

#include <array>
#include <algorithm>

#include "dtypes.h"
#include "fifo_fixed_size.h"

namespace Algorithms {

template<typename T, size_t N> class median_filter{
private:
  static constexpr size_t fifo_size = (N<<1)+1;
  Datastructures::fifo_fixed_size<T,fifo_size> ffs;
public:
  median_filter()=default;
  ~median_filter()=default;

  /**
   * @brief put - add data to filter
   * @param _x
   */
  void put(T const& _x){
    ffs.put(_x);
    return;
  }

  std::array<T,fifo_size> const& buffer() const{
    return ffs.buffer();
  }

  /**
   * @brief get - get filtered data
   * @return
   */
  T get() const{
    std::array<T,fifo_size> tmp;
    auto const& ref = ffs.buffer();
    std::copy(ref.begin(), ref.end(), tmp.begin());
    std::stable_sort(tmp.begin(), tmp.end(), std::greater<T>());
    return tmp[fifo_size>>1];
  }

};

} //namespace

#endif // MEDIAN_FILTER_H
