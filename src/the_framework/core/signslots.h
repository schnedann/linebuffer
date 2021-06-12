/******************************************************************************/
/** C++17 style signal and slots                                             **/
/** loosely inspired by Sarah Thompson's C++ Signal/Slot Library found at    **/
/** https://sourceforge.net/projects/sigslot/                                **/
/** Danny Schneider, 2019-2021                                               **/
/******************************************************************************/

/*
 * Copyright (c) 2019-2021, Danny Schneider
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 * this list of conditions and the following disclaimer. (of course you are
 * allowed to extend the above copyright notice by the means of adding your
 * name and date if and only if you have contributed to the source)
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 * this list of conditions and the following disclaimer in the documentation
 * and/or other materials provided with the distribution.
 *
 * 3. Redistributions of any forked and or modified version of this code in binary
 * form need to make the source code availible upon request. If maintainance of any
 * forked and or modified version of this code is stopped, future access to the code
 * needs to be ensured e.g. by at least uploading it to an public open platform and
 * or the official original repository if availible.
 *
 * 4. Usage of this code (stating Discrimination Against Fields of Endeavor [*1] )
 * neither in source nor in binary form - in any military, intelligence,
 * public surveillance, surveillance state , political supression context is forbidden
 * Simply:
 * do not use this software to harm people or to violate non-derogable human rights
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
 * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * [*1]: Comment of Conndition 4, yes this conndition violates the Open Source Definition
 * But as an Engineer with a german background I do believe you are responsible how the
 * things are used you develop. So yes, even if Conndition 4 might be circumvented and/or
 * be ignored by bad people, I want to state with this liecense, that my intend is to not
 * have the software used to harm people, and I want to ask you to respect this.
 */

/**************************************************
 * Essentially signals are triggers for multiple callbacks
 * So you can register multiple callbacks, called slots, to
 * a single signal and when the signal is triggered, it emits
 * a given set of parameters to all these callbacks.
 * Another usefull usecase is to interconnect functional blocks
 * according to the information flow
 *
 * Core Features:
 * - modern template code which enables almost unlimited
 *   number of parameters exchanged between a signal and
 *   a slot,
 * - combining C++17 features + the stdlib allows for very
 *   compact code
 * - the use of std::function allows a signal to connect
 *   to any function, to non-static methods or lambdas
 **************************************************/
#ifndef SIGNSLOTS_H
#define SIGNSLOTS_H

#include <mutex>
#include <thread>
#include <functional>
#include <vector>
#include <tuple>

#include "dtypes.h"
#include "iterators.h"
#include "math_discrete.h"

namespace SIGNALS_N_SLOTS {

//Simplify type
template<typename T> using it_t = Core::Container::weak_ptr_t<T>;

/**************************************************
 * Slot
 * A thread-save wrapper for an worker callback
 **************************************************/

//Forward declareations
class signal_base;

/**************************************************
 * Slot Management for Signals
 **************************************************/

/**
 * @note Curiously recurring template pattern
 */
template<typename CRTP> class slot_mngt{
private:
  //List of Pointers to Signals
  std::vector<it_t<signal_base>> connected_signals_list{};
public:
  slot_mngt()=default;
  slot_mngt(slot_mngt const&)=delete;
  slot_mngt(slot_mngt &&)=delete;
  ~slot_mngt(){
    //For all connected signals
    for(auto consig:this->connected_signals_list){
      //signal Pointer is valid?
      if(Core::Container::is_valid(consig)){
        consig->deregister();
      }
    }
    return;
  }

  void register_slot(signal_base& sig){
    connected_signals_list.push_back(&sig);
    return;
  }
};

/**************************************************
 * Signal-Base
 * used for auto-deregestration of slotified classes
 * provides deregister Interface
 **************************************************/

class signal_base{
private:
  //nothing
public:
  signal_base()=default;
  ~signal_base()=default;

  void deregister(){
    //this->
    return;
  }
};

//-----

/**
 * @brief signal_dereg_if - Deregister Interface
 * @note Curiously recurring template pattern
 */
template<typename CRTP> class signal_dereg_if:public signal_base{
private:
  //none
public:
  signal_dereg_if()=default;
  signal_dereg_if(signal_dereg_if const&)=delete;
  signal_dereg_if(signal_dereg_if &&)=delete;

  void deregister(){
    //rederict deregister to the derived class specific implementation
    (static_cast<CRTP*>(this))->deregister_impl();
  }
};

/**************************************************
 * Signal
 * esentially this is a event to multi-callback manager
 **************************************************/

template<typename... T> class signal:public signal_dereg_if<signal<T...>>{
private:
  //Mutex protecting slot_trigger_list
  std::mutex list_m;
  //List of Slot-Callbacks
  std::vector<std::function<void(std::tuple<T...> const&)>> slot_trigger_list;

  //Template specific deregister
  void deregister_impl(){

    return;
  }

public:
  signal()=default;
  signal(signal const&)=delete;
  signal(signal&&)=delete;
  ~signal()=default;

  /**
   * @brief emit - Emit Signal, so Slots receive Callback
   * @param _v   - Tupple which holds all parameters which are transmitted via the signal
   */
  void emit(std::tuple<T...> const& _v){
    std::scoped_lock lock(list_m); //(C++17)
    //send Signal to all connected Slots
    for(auto st:slot_trigger_list){
      if(st) st(_v); //Call registered Callback if exists
    }
    return;
  }

  /**
   * @brief operator () - use signal like it is a function to emit it
   * @param _v
   */
  void operator()(std::tuple<T...> const& _v){
    return emit(_v);
  }

  /**
   * @brief connect - Connect a Callback (function, method or lambda) as "Slot"
   * @param clbk, which is executed when the Signal is emmited
   * @return the slot-Id
   */
  u32 connect(std::function<void(std::tuple<T...> const&)> const& clbk){
    u32 slot_id = u32(slot_trigger_list.size());
    std::scoped_lock lock(list_m); //(C++17)
    slot_trigger_list.push_back(clbk);
    return slot_id;
  }

  /**
   * @brief disconnect - Search for an Slot with an given ID, and if it exists, delete it from the List
   * @param slot_id - this is the index of an Slot in the slot_trigger_list
   */
  void disconnect(u32 slot_id){
    if(slot_id<slot_trigger_list.size()){
      auto it = slot_trigger_list.begin();
      std::advance(it,slot_id);
      std::scoped_lock lock(list_m); //(C++17)
      slot_trigger_list.erase(it);
    }
    return;
  }
};

//-----

/**
 * @brief The indicator class - Variant of signal without parameters (= no data),
 *                              It just transports an event like a 'trigger'
 */
class indicator{
private:
  u32 max_id;
  //Mutex protecting slot_trigger_list
  std::mutex list_m;
  //List of Slot-Callbacks
  std::vector<std::function<void()>> slot_list;
public:
  indicator()=default;
  ~indicator()=default;

  void emit();       //send the signal
  void operator()(); //function like alias for emit
  u32 connect(std::function<void()> const& clbk); //connect a slot to the signal
  void disconnect(u32 slot_id);                   //remove a slot from the signal
};

/**************************************************
 *
 **************************************************/

} //namespace

#endif // SIGNSLOTS_H
