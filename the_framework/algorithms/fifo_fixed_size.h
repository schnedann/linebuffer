#ifndef FIFO_FIXED_SIZE_H
#define FIFO_FIXED_SIZE_H

#include <array>

#include "dtypes.h"

namespace Algorithms {

template<typename T, size_t N> class fifo_fixed_size{
private:
  size_t idx{0};
  std::array<T,N> fifo{};
  bool filled{false};
public:
  fifo_fixed_size()=default;
  ~fifo_fixed_size()=default;

  void put(T const& _x){
    fifo[idx] = _x;
    idx = ((idx+1)%N);
    if(0==idx){filled=true;}
    return;
  }

  bool const& is_filled() const{
    return filled;
  }

  T& get(){
    auto idy = (filled)?(idx):(0);
    return fifo[idy];
  }

  std::array<T,N>& buffer(){
    return fifo;
  }

  /*T& get_mid(){

  }*/
};

} //namespace

#endif // FIFO_FIXED_SIZE_H
