#include "mutual_lock.h"

#include "bitmacros.h"

static constexpr u8 const shift_by_2 = 2;

/**
 * @brief SYNC::LOCK::Mutual::lock
 * @param id
 * @return
 */
void SYNC::LOCK::Mutual::wait_lock(IDs_t const id){

  if(id == SYNC::LOCK::IDs_t::ID_A){
    wants_to_enter_A = true;
    turn = SYNC::LOCK::IDs_t::ID_B;

    while(wants_to_enter_B && (turn==SYNC::LOCK::IDs_t::ID_B)){}
  }else{
    wants_to_enter_B = true;
    turn = SYNC::LOCK::IDs_t::ID_A;

    while(wants_to_enter_A && (turn==SYNC::LOCK::IDs_t::ID_A)){}
  }
  return;
}

/**
 * @brief SYNC::LOCK::Mutual::is_locked
 * @param id
 * @return
 */
bool SYNC::LOCK::Mutual::is_locked(IDs_t const id){
  return (id == SYNC::LOCK::IDs_t::ID_A)?(wants_to_enter_A && turn==SYNC::LOCK::IDs_t::ID_A):(
                                          wants_to_enter_B && turn==SYNC::LOCK::IDs_t::ID_B);
}

/**
 * @brief SYNC::LOCK::Mutual::release
 * @param id
 */
void SYNC::LOCK::Mutual::release(IDs_t const id){
  if(id == SYNC::LOCK::IDs_t::ID_A){
    wants_to_enter_A = false;
    turn = SYNC::LOCK::IDs_t::ID_B;
  }else{
    wants_to_enter_B = false;
    turn = SYNC::LOCK::IDs_t::ID_A;
  }
  return;
}
