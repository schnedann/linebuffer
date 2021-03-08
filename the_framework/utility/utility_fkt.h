#ifndef UTILITY_FKT_H_
#define UTILITY_FKT_H_

#ifdef __cplusplus
  extern "C" {
#endif

/********************
 * Includes         *
 ********************/

//System Includes

//Project Includes
#include "dtypes.h"
//Module Includes

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

/****************************************
 * Macros
 ****************************************/

		

/****************************************
 * Module public Data (global)
 ****************************************/

//Init Value for Integrator Control
extern const integrate_t init_for_ictrl;

/****************************
 * Module Public Functions *
 ****************************/

//-----
s16 integrate(integrate_t* ictrl ,s16 v);
s16 modpid(s16 w, s16 x, modpid_t* pidctrl);

#ifdef __cplusplus
  }
#endif

#endif

