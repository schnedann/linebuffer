#ifndef CONTROL_PID_H
#define CONTROL_PID_H

/********************
 * Includes         *
 ********************/

//System Includes

//Project Includes
#include "dtypes.h"
//Module Includes
#include "iterators.h"
#include "ovf_save.h"

/********************
 * Defines          *
 ********************/



/****************************************
 * Typedefs & Structs
 ****************************************/

typedef struct integrate_st{
  s16 KiTN;
  s16 KiD;
  s16 old_y;
  s16 old_x;
}integrate_t;
using integrate_t = struct integrate_st;

typedef struct modpid_st{
  s16 KpN;
  s16 KpD;
  s16 K1N;
  s16 K1D;
  s16 K2N;
  s16 K2D;
  s16 old_e;
  s16 old_x1;
  s16 old_x2;
}modpid_t;
using modpid_t = struct modpid_st;

/****************************************
 * Macros
 ****************************************/



/****************************************
 * Module public Data (global)
 ****************************************/

/****************************
 * Module Public Functions *
 ****************************/

//----- Simple Integrator

/**
 * Basic Integrator
 */
template<typename T, typename RT> RT integrate(Core::Container::iterator_t<integrate_t> ictrl ,s16 const x){
  u32 e = Math::OverflowSafe::satt_sadd(x,ictrl->old_x);
  e *= ictrl->KiTN;
  e /= ((u32)ictrl->KiD); // * 2);
  if(e > Math::Boolean::__MAX_SIGNED<u16>()) e =  Math::Boolean::__MAX_SIGNED<u16>();
  if(e < Math::Boolean::__MIN_SIGNED<u16>()) e =  Math::Boolean::__MIN_SIGNED<u16>();
  ictrl->old_x = x;
  ictrl->old_y = Math::OverflowSafe::satt_sadd<u16>(ictrl->old_y,(u16)e);
  return ictrl->old_y;
}

//----- PID Modificated

/**
 *
 */
template<typename T, typename RT> RT modpid(s16 w, s16 x, Core::Container::iterator_t<modpid_t> pidctrl){
  u32 res = pidctrl->K1N;
  u32 tmp = pidctrl->K2N;
//---
  s16 e =  Math::OverflowSafe::satt_ssub(w,x);
  res *= Math::OverflowSafe::satt_ssub(e,pidctrl->old_e);
  res /= pidctrl->K1D;
  pidctrl->old_e = e;
  if(res > Math::Boolean::__MAX_SIGNED<u16>()) res =  Math::Boolean::__MAX_SIGNED<u16>();
  if(res < Math::Boolean::__MIN_SIGNED<u16>()) res =  Math::Boolean::__MIN_SIGNED<u16>();
//---
  tmp *= Math::OverflowSafe::satt_sadd(Math::OverflowSafe::satt_ssub(x,(2*pidctrl->old_x1)),pidctrl->old_x2);
  tmp /= pidctrl->K2D;
  if(tmp > Math::Boolean::__MAX_SIGNED<u16>()) tmp =  Math::Boolean::__MAX_SIGNED<u16>();
  if(tmp < Math::Boolean::__MIN_SIGNED<u16>()) tmp =  Math::Boolean::__MIN_SIGNED<u16>();
//---
  tmp = Math::OverflowSafe::satt_ssub((u16)res,(u16)tmp);
  res = pidctrl->KpN;
  res *= tmp;
  res /= pidctrl->KpD;
  if(res > Math::Boolean::__MAX_SIGNED<u16>()) res =  Math::Boolean::__MAX_SIGNED<u16>();
  if(res < Math::Boolean::__MIN_SIGNED<u16>()) res =  Math::Boolean::__MIN_SIGNED<u16>();
//---
  pidctrl->old_x2 = pidctrl->old_x1;
  pidctrl->old_x1 = x;
//---
  return (u16)res;
}

#endif // CONTROL_PID_H
