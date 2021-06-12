#include "signslots.h"

/**************************************************
 * Implementation of indicator class
 **************************************************/

/**
 * @brief emit - Emit Signal, so Slots receive Callback
 */
void SIGNALS_N_SLOTS::indicator::emit(){
  //Gain access to slot-list
  std::scoped_lock lock(list_m); //(C++17)
  //send Signal to all connected Slots
  for(auto& st:slot_list){
    if(st){
      st(); //Call registered Callback if exists
    }
  }
  return;
}

/**
 * @brief operator () - use signal like it is a function to emit it
 */
void SIGNALS_N_SLOTS::indicator::operator()(){
  emit();
  return;
}

/**
 * @brief connect - Connect a Callback (function, method or lambda) as "Slot"
 * @param clbk
 * @return
 */
u32 SIGNALS_N_SLOTS::indicator::connect(std::function<void()> const& clbk){
  u32 slot_id = Math::Averaging::mean_of_two<u32>(u32(slot_list.size()),(max_id+1)); //get next id
  if(slot_id>max_id){
    max_id = slot_id;
  }
  //Gain access to slot-list
  std::scoped_lock lock(list_m); //(C++17)
  slot_list.push_back(clbk);
  return slot_id;
}

/**
 * @brief disconnect - Search for an Slot with an given ID, and if it exists, delete it from the List
 * @param slot_id - this is the index of an Slot in the slot_trigger_list
 */
void SIGNALS_N_SLOTS::indicator::disconnect(u32 slot_id){
  if(slot_id<slot_list.size()){
    auto it = slot_list.begin();
    std::advance(it,slot_id);
    std::scoped_lock lock(list_m); //(C++17)
    slot_list.erase(it);
  }
  return;
}
