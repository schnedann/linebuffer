/**************************************************
 * Utility-functions
 * Collection of unrelated usefull C-Code
 * by Danny Schneider, 2000-2014
 **************************************************/

/********************
 * Includes         *
 ********************/

//System Includes

//Project Includes
#include "dtypes.h"
//Module Includes
#include "bitmacros.h"
#include "math_discrete.h"
#include "ovf_save.h"
#include "utility_fkt.h"

using namespace Math::Discrete;
using namespace Math::OverflowSafe;

/********************
 * Defines          *
 ********************/

//none

/****************************************
 * Typedefs & Structs
 ****************************************/

//none

/**************************
 * Modul global data      *
 **************************/

//none

/**************************
 * Modul local prototypes *
 **************************/

//none

/********************
 * Module-Code      *
 ********************/

//----- Simple Integrator

const integrate_t init_for_ictrl = {0,0,0,0};

/**
 * Basic Integrator
 */
s16 integrate(integrate_t* ictrl ,s16 x){
/*
  u32 e = satt_sadd(x,ictrl->old_x);
  e *= ictrl->KiTN;
  e /= ((u32)ictrl->KiD); // * 2);
  if(e > Math::Boolean::__MAX_SIGNED<u16>()) e =  Math::Boolean::__MAX_SIGNED<u16>();
  if(e < Math::Boolean::__MIN_SIGNED<u16>()) e =  Math::Boolean::__MIN_SIGNED<u16>();
  ictrl->old_x = x;
  ictrl->old_y = Math::OverflowSafe::satt_sadd<u16>(ictrl->old_y,(u16)e);
  return ictrl->old_y;
*/
  return 0;
}

//----- PID Modificated

/**
 *
 */
s16 modpid(s16 w, s16 x, modpid_t* pidctrl){
/*
  u32 res = pidctrl->K1N;
  u32 tmp = pidctrl->K2N;
//---
  s16 e =  satt_ssub(w,x);
  res *= satt_ssub(e,pidctrl->old_e);
  res /= pidctrl->K1D;
  pidctrl->old_e = e;
  if(res > Math::Boolean::__MAX_SIGNED<u16>()) res =  Math::Boolean::__MAX_SIGNED<u16>();
  if(res < Math::Boolean::__MIN_SIGNED<u16>()) res =  Math::Boolean::__MIN_SIGNED<u16>();
//---
  tmp *= satt_sadd(satt_ssub(x,(2*pidctrl->old_x1)),pidctrl->old_x2);
  tmp /= pidctrl->K2D;
  if(tmp > Math::Boolean::__MAX_SIGNED<u16>()) tmp =  Math::Boolean::__MAX_SIGNED<u16>();
  if(tmp < Math::Boolean::__MIN_SIGNED<u16>()) tmp =  Math::Boolean::__MIN_SIGNED<u16>();
//---
  tmp = satt_ssub((u16)res,(u16)tmp);
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
*/
  return 0;
}

//--------------------------------------------------------------------------------

