#ifndef MINMAX_H
#define MINMAX_H

#include "bitmacros.h"

template<typename T> class minmax
{
private:
    T min{0}; //wrong value!!!
    T max{0};
public:
    minmax();
    void put(T const _v){
      if(_v>max) max=_v;
      if(_v<min) min=_v;
    }
    T get_min(){
      return min;
    }
    T get_max(){
      return max;
    }
};

#endif // MINMAX_H
