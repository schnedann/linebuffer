/******************************************************************************/
/* Ringbuffer with linked lists                                               */
/* configureable,resizeable Ringbuffers                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Copyright Danny Schneider, 2009                                            */
/******************************************************************************/

#ifndef _RINGBUFFER_SLL_H_
#define _RINGBUFFER_SLL_H_

#ifdef __cplusplus
extern "C"
{
#endif

/********************
 * Includes
 ********************/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "rb_conf.h"

/********************
 * Defines
 ********************/

#define RB_NULL     0x0
#define RB_EMPTY    0x1
#define RB_OVERFLOW 0x2
#define RB_FULL     0x4

/********************
 * Structures / Unions
 ********************/

/** Buffer Element
 *  Double Linked List
 */
typedef struct stRB_Elem{
    struct stRB_Elem *previous;
    struct stRB_Elem *next;
    RB_DATATYPE *data;
}RB_Elem;

/** Buffer Control Structure
 *
 */
typedef struct{
    RB_Elem *base;    //List-Base
    RB_Elem *read;    //Read-Pointer
    RB_Elem *write;   //Write-Pointer
    uint8_t rbsbfa;   //
    uint32_t count_e; //Number of Elements
}RB_CTRL;

/********************
 * Fkt-Headers
 ********************/

void init_rb(uint32_t noe, RB_DATATYPE initvar);
uint32_t getcount_rb(void);

 void add_elem(RB_DATATYPE e);
uint32_t find_elem(RB_DATATYPE e);
RB_DATATYPE get_elem(uint32_t nr);
void del_elem(RB_DATATYPE e,uint8_t mode);
void push_elem(RB_DATATYPE e);
RB_DATATYPE pop_elem(void);
uint32_t count_elem(RB_DATATYPE e);

#ifdef __cplusplus
}
#endif

#endif

//EOF
