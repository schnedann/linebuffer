/**
 * Software Timer
 * single timertick counter 32Bit
 * shellsort based organization, support for up to 65536 unique Timers at once
 * state machine definition included for seamles Operational System integration
 */


#ifndef SWTIMER_H
#define SWTIMER_H

#include <array>
#include <vector>
#include <functional>

#include "dtypes.h"
#include "bitmacros.h"

namespace Core {

namespace SWTimer {

template<typename T> using swtime_t = T;
using swtime_uid_t = u32;

template<typename T> static constexpr swtime_t<T> const maxtime = Math::Boolean::GETFULLMASK<T>();

using SWTimer_state_t = u8;
struct SWTimer_state_st{
  SWTimer_state_t free;     //unused
  SWTimer_state_t waiting;  //added, waiting for trigger
  SWTimer_state_t running;  //triggered & active
  SWTimer_state_t elapsed;  //Stop Time reached
  SWTimer_state_t finished; //Timer Event processed, wait for cleanup
  SWTimer_state_t invalid;
}SWTimer_state_def = {0,1,2,4,8,128};

//Single Timer Entry
template<typename T> struct SWTimer_Entry{
  swtime_uid_t    id;
  SWTimer_state_t state;
  swtime_t<T>     stop;
};

template<typename T> class SWTimer{
private:
  u32 idgen{0};
  swtime_t<T> timeticks{0};
  std::vector<SWTimer_Entry<T>> timer_lst{0};

  /**
   * @brief sort_timer - Shellsort...
   */
  void sort_timer(){
    #define SWT_SORT_SET 1
  #if SWT_SORT_SET == 1
    u8 const stepwidth_size = 12;
    constexpr std::array<u16,12> const stepwidth = {
      //1, 4, 10, 23, 57, 132, 301, 701, 1753, 4383, 10958, 27396
      27396, 10958, 4383, 1753, 701, 301, 132, 57, 23, 10, 4, 1
    };
  #endif
  #if SWT_SORT_SET == 2
    u8 const stepwidth_size = 11;
    constexpr std::array<u16,11> const stepwidth = {
      /*2147483647, 1131376761, 410151271, 157840433, 58548857,
      21521774, 8810089, 3501671, 1355339, 543749, 213331, 84801,*/
      27901, 11969, 4711, 1968, 815, 271, 111, 41, 13, 4, 1
    };
  #endif
    for(size_t ik = 0; ik < stepwidth_size; ++ik){
      size_t h = stepwidth[ik];
      // Sortiere die "Spalten" mit Insertionsort
      for(size_t ii = h; ii < n; ++ii){
        SWTimer_Entry t = timer_lst[ii];
        size_t ij = ii;
        while ((ij >= h) && (timer_lst[ij-h] > t)){
          timer_lst[ij] = timer_lst[ij-h];
          ij = ij - h;
        }
        timer_lst[ij] = t;
      }
    }
    return;
  }

  bool cmp_gt(SWTimer_Entry<T> const& a, SWTimer_Entry<T> const& b){
  bool res = false;
    //Lower State --> higer Prio
    res |= (a.state < b.state)?(true):(false);
    //Same State?
    if(a.state == b.state){
      //
      res |= (a.stop > b.stop)?(true):(false);
    }
    return res;
  }

  /**
   * @brief SWTimer::diff
   * @param a
   * @param b
   * @return
   */
  swtime_t<T> diff(SWTimer_Entry<T> const& a, SWTimer_Entry<T> const& b){
    swtime_t res = 0;
    if(a>=b){
      res = a-b;
    }else{
      res = maxtime-b+a;
    }
    return res;
  }

  /**
   * @brief SWTimer::advance
   */
  void advance(){
    ++timeticks;
    return;
  }

public:
  SWTimer()=default;
  ~SWTimer()=default;

  /**
   * @brief SWTimer::execute
   */
  void execute(){ //Cyclic Call
  advance();

  if(timer_lst.size() > 0){
    bool elapsed    = false;
    bool moretimers = false;
    do{
      elapsed = (timeticks >= timer_lst.front().stop)?(true):(false);
//Callback here
      timer_lst.erase(timer_lst.begin());
      moretimers = (timer_lst.size())?(true):(false);
    }while(elapsed && moretimers);
  }

  return;
}

  //void add_timer(entry_t const& timer);

  /**
   * @brief SWTimer::add_timer
   * @param wtime
   * @return
   */
  swtime_uid_t add_timer(SWTimer_Entry<T> const& wtime, const bool &start);
{
  entry_t timer;
  timer.id = ++idgen; //Generate new ID

  { //Calculate new stop-time
    swtime_t ctime = timeticks;     //current Time
    swtime_t diff  = maxtime-ctime; //Time to Overflow of Tickcounter
    if(diff>=wtime){                //no overflow
      timer.stop = ctime+diff;
    }else{                          //overflow
      timer.stop = (wtime-diff)-1;
    }
  }

  timer.state = (start)?(swt_running):(swt_waiting);
  timer_lst.push_back(timer); //Add new Timer 2 List
  sort_timer();               //Sort Timer List
  return timer.id;
}

  /**
   * @brief SWTimer::add_timer
   * @param id
   * @param wtime
   */
  bool add_timer(swtime_uid_t const& id, SWTimer_Entry<T> const& wtime, bool const& start){
    bool noerr = false;
    entry_t timer;

    //Search if Timer with ID exists, is free or finished
    for(entry_t& x:timer_lst){
      if(timer.id == id){
        if((timer.state == swt_free) || (timer.state == swt_finished)){
          timer = x;
          noerr = true;
          break;
        }
      }
    }

    //if Timer with ID exists, is free or finished...
    if(noerr){
      { //Calculate new stop-time
        swtime_t ctime = timeticks;     //current Time
        swtime_t diff  = maxtime-ctime; //Time to Overflow of Tickcounter
        if(diff>=wtime){                //no overflow
          timer.stop = ctime+diff;
        }else{                          //overflow
          timer.stop = (wtime-diff)-1;
        }
      }

      timer.state = (start)?(swt_running):(swt_waiting);
      timer_lst.push_back(timer); //Add new Timer 2 List
      sort_timer();               //Sort Timer List
    }

    return noerr;
  }


  void stop_timer(swtime_uid_t const& id);

  /**
   * @brief info_timer
   * @param id
   * @return
   */
  SWTimer_state_t info_timer(swtime_uid_t const& id){
    auto res = SWTimer_state_def.invalid;
    for(auto& swt:timer_lst){
      if(swt.id == id){
        res = swt.state;
        break;
      }
    }
    return res;
  }

  bool expired_timer(swtime_uid_t const& id, bool const& restart);


private:

};

} //namespace

} //namespace

#endif // SWTIMER_H
