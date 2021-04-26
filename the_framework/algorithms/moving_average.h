#ifndef MOVING_AVERAGE_H
#define MOVING_AVERAGE_H

#include <cstdint>
#include <array>

template<typename T, size_t N> class moving_average{
private:
  T cma;
  size_t idx;
  T sma;
  std::array<T,N> fifo{};

public:
  moving_average():cma(T()),idx(0),sma(0){}

  /**
   * @brief cumulative
   * @param value
   * @return
   */
  T cumulative(T value){
    cma = (cma + value)/2;
    return cma;
  }

  /**
   * @brief simple
   * @param value
   * @return
   */
  T simple(T value){
    fifo[idx]=value;
    idx = ((idx+1)%N);
    sma = fifo[0];
    for(size_t ii=1; ii<fifo.size(); ++ii){
      sma = (sma+fifo[ii])/2;
    }
    return sma;
  }

  T get_c(){
    return cma;
  }

  T get_s(){
    return sma;
  }
};

#endif // MOVING_AVERAGE_H
