#ifndef STOPWATCH_H
#define STOPWATCH_H

#include <iostream>
#include <string>
#include <chrono>

#include "dtypes.h"

namespace Benchmark {

//using tspan_t = std::chrono::duration<s64,std::chrono::nanoseconds>;
using now_t = std::chrono::time_point<std::chrono::system_clock>;

now_t get_current_time(){
  return std::chrono::system_clock::now();
}

s64 trigger(now_t& start, bool const retrigger=false){
  auto end = get_current_time();
  auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);
  if(retrigger){
    start = end;
  }
  return duration.count();
}

//-----

template<class CRTP> class stopwatch{
private:
  now_t start{};
public:
  //constructor
  //stopwatch():start(get_current_time()){}

  void bench(){
    start = std::chrono::system_clock::now();
    (reinterpret_cast<CRTP*>(this))->impl_bench_worker();
    std::cout << "elapsed time: " << trigger(start) << "[ns]" << "\n";
  }
};

} //namespace

#endif // STOPWATCH_H
