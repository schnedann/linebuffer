/**************************************************
 * track min & max of a value
 **************************************************/

#ifndef MINMAX_H
#define MINMAX_H

namespace Algorithms {

template<typename T> class minmax{
private:
    T min{0};
    T max{0};
public:
    minmax()=delete;
    minmax(T const& _min, T const& _max):min(_min),max(_max){}
    minmax(minmax const& other):min(other.min),max(other.max){}
    minmax(minmax&& other):min(other.min),max(other.max){}
    ~minmax()=default;

    void put(T const _v){
      if(_v>max){
        max=_v;
      }
      if(_v<min){
        min=_v;
      }
      return;
    }
    T get_min(){
      return min;
    }
    T get_max(){
      return max;
    }
};

} //Algorithms

#endif // MINMAX_H
