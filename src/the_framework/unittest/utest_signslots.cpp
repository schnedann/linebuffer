#include <array>
#include <thread>
#include <chrono>
#include <random>
#include <mutex>

#include "catch.hpp"

#include "dtypes.h"
#include "signslots.h"

using namespace std;

u64 check1(u16 _a){
  if(_a>0){
    auto tmp = check1(_a-1);
    return (tmp*tmp)+_a;
  }else{
    return 1;
  }
}

TEST_CASE( "SIGNALS_N_SLOTS", "[callbacks]" ) {

  SECTION("SIGNALS_N_SLOTS"){
    std::random_device rd;  //Will be used to obtain a seed for the random number engine
    std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
    std::uniform_int_distribution<u16> distrib(1, 1000);

    SIGNALS_N_SLOTS::signal<u64> sig_value;
    SIGNALS_N_SLOTS::signal<u16> sig_index;

    u64 _x{0};
    auto fct = [&_x](std::tuple<u16> const _a){
      _x = (_x * _x) + std::get<0>(_a);
      return;
    };

    u16 _i{0};


    std::mutex rng_mutex;

    /**
     * Fädchen1 - Worker
     */
    auto t1 = [&distrib,&gen,&rng_mutex](){
      std::lock_guard<std::mutex> const lock(rng_mutex);
      auto sleep_time = std::chrono::microseconds(distrib(gen));
      std::this_thread::sleep_for(sleep_time);
    };

    /**
     * Fädchen2 - Worker
     */
    auto t2 = [&distrib,&gen,&rng_mutex](){
      std::lock_guard<std::mutex> const lock(rng_mutex);
      auto sleep_time = std::chrono::microseconds(distrib(gen));
      std::this_thread::sleep_for(sleep_time);
    };

    std::thread faedchen1(t1);
    std::thread faedchen2(t2);
    faedchen1.join();
    faedchen2.join();
  }

  SECTION("SIGNALS_N_SLOTS::signal<u16> - order"){
    u64 _x{1};

    auto fct = [&_x](std::tuple<u16> const _a){
      _x = (_x * _x) + std::get<0>(_a);
      return;
    };

    SIGNALS_N_SLOTS::signal<u16> sig; //sending a signal with a u16 as data
    sig.connect(fct);                 //assign a slot which receives the data

    for(u16 ii=0; ii<25; ++ii){
      sig.emit(ii);
      auto ref = check1(ii);
      REQUIRE( ref == _x );
    }
  }

  SECTION( "SIGNALS_N_SLOTS::signal<u32> - basic chain" ) {
    constexpr static u32 const cnt = 5000;

    //Some Signals
    array<SIGNALS_N_SLOTS::signal<u32>,cnt> siglst;

    //The Worker Callback
    u32 res = 0;
    auto fct = [&siglst,&res](std::tuple<u32> _x){
      u32 idx = get<0>(_x);

      if(0!=(idx%3)){
         res = idx;
      }else{
        if((idx>0) && (0!=((idx-1)%3))){
          REQUIRE( res == (idx-1) );
        }
      }

      ++idx;
      if(idx<siglst.size()){
        siglst[idx].emit(std::make_tuple(idx));
      }
      return;
    };

    //Connect each Signal to the Worker
    for(auto& sig:siglst){
      sig.connect(fct);
    }

    //Emit first Signal to start Chain
    siglst[0].emit(std::make_tuple(res));
    //Check after Chain has terminated
    REQUIRE( res == (cnt-1) );
  }

  SECTION( "SIGNALS_N_SLOTS::indicator - basic chain" ) {
    constexpr static u32 const cnt = 5000;

    //Some Signals
    array<SIGNALS_N_SLOTS::indicator,cnt> siglst;

    //The Worker Callback
    u32 res = 0;
    auto fct = [&siglst,&res](){
      ++res;
      if(res<siglst.size()){
        siglst[res].emit();
      }
      return;
    };

    //Connect each Signal to the Worker
    for(size_t ii=0; ii<siglst.size(); ++ii){
      siglst[ii].connect(fct);
    }

    //Emit first Signal to start Chain
    siglst[0].emit();
    //Check after Chain has terminated
    REQUIRE( res == cnt );
  }
}
