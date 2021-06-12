/******************************************************************************/
/* Ringbuffer with linked lists                                               */
/* configureable,resizeable Ringbuffers                                       */
/*                                                                            */
/*----------------------------------------------------------------------------*/
/* Copyright Danny Schneider, 2009                                            */
/******************************************************************************/

#include "ringbuffer_ll.h"

/********************
 * Macros
 ********************/

// FLAG Handling
#define bSet(_x,_mask)    (((_x)&(_mask))>0)      //is Bit Set?
#define bnSet(_x,_mask)   (((_x)&(_mask))==0)     //is Bit not Set?
#define Setb(_x,_mask)    ((_x)|=(_mask))         //Set Bit
#define Clearb(_x,_mask)  ((_x)&=~(_mask))        //Clear Bit
#define Toggleb(_x,_mask) ((_x)^=(_mask))         //Toggle Bit

/********************
 * Module Global Varibles
 ********************/

RB_CTRL rb;             //Control Structure
RB_CTRL *rb_ptr = &rb;  //Pointer to Ctrl-Structure

/********************
 * Public Functions
 ********************/

/** Initialisize the Ringbuffer
 *  noe    : Number of Elements
 *  initvar: Initial Value of Elements
 */
void init_rb(uint32_t noe, RB_DATATYPE initvar){
    uint32_t ii;

    //Init Control Structure
    rb_ptr->base    = NULL;
    rb_ptr->read    = NULL;
    rb_ptr->write   = NULL;
    rb_ptr->rbsbfa  = RB_NULL;
    rb_ptr->count_e = 0;

    //Build buffer with initial capacity
    for(ii=0; ii<noe; ++ii){
        add_elem();
    }
    return;
}

/** Add a new Element to the Ringbuffer
 *  increasing the buffer capacity
 *  chain in in front of the write pointer
 */
void add_elem(){
    RB_Elem *tmp_ptr;

    //Create new Element
    tmp_ptr = (RB_Elem*) calloc(1,sizeof(RB_Elem));
    tmp_ptr->data = NULL;

    if(bSet(rb_ptr->rbsbfa,RB_NULL)){
        //Set link-pointer of new Element
        tmp_ptr->previous = tmp_ptr;
        tmp_ptr->next     = tmp_ptr;
        //Chain new Element into the List
        rb_ptr->base = tmp_ptr;
        //Buffer now contains at least one empty Element
        Setb(rb_ptr->rbsbfa,RB_EMPTY);
    }else{
        //Set link-pointer of new Element
        tmp_ptr->previous = rb_ptr->write;
        tmp_ptr->next     = rb_ptr->write->next;
        //Chain new Element into the List
        tmp_ptr->previous->next = tmp_ptr;
        tmp_ptr->next->previous = tmp_ptr;
        //Buffer now has at least one empty Element to fill
        //Overflow Condition is unchanged
        Clearb(rb_ptr->rbsbfa,RB_FULL);
    }
    //Count new Element
    ++(rb_ptr->count_e);
    return;
}

/** get number of Elements
 *
 */
uint32_t getcount_rb(void){
    return rb_ptr->count_e;
}

/**
 *
 */
void push_elem(RB_DATATYPE e){
    RB_Elem *tmp_ptr;

    //Buffer has Elements and is not FULL?
    if(bnSet(rb_ptr->rbsbfa,RB_NULL) && bnSet(rb_ptr->rbsbfa,RB_FULL)){

        rb_ptr->write->data =

        rb_ptr->write = rb_ptr->write->next;
    }
    return;
}

/**
 *
 */
RB_DATATYPE pop_elem(void){
    RB_DATATYPE res;

    //Buffer has Elements and is not EMPTY?
    if(bnSet(rb_ptr->rbsbfa,RB_NULL) && bnSet(rb_ptr->rbsbfa,RB_EMPTY)){

        res = *(rb_ptr->read->data);

        rb_ptr->read = rb_ptr->write->read;
    }
    return res;
}

/********************
 * Private Functions
 ********************/

/** Delete a Buffer Element
 *
 */
void del_elem(RB_Elem *tmp_ptr){

    RB_Elem *s_ptr

    if(tmp_ptr != NULL && bnSet(rb_ptr->rbsbfa,RB_NULL))
        /*******************************
         * Delete Element
         *******************************/
        //At least two Elements?
        if(rb_ptr->count_e > 1){
            //Delete Element at base pointer?
            if(tmp_ptr == rb_ptr->base){
                //Set new base pointer
                rb_ptr->base = tmp_ptr->next;
            }
            //Chain Out the Element
            tmp_ptr->previous->next = tmp_ptr->next;
            tmp_ptr->next->previous = tmp_ptr->previous;
        }
        //Free Memory
        free(tmp_ptr);
        //unCount deleted Element
        --(rb_ptr->count_e);

        /*******************************
         *Check / Correct Buffer Status
         *******************************/
        //Correct Read-Pointer if necessary
        if(tmp_ptr == rb_ptr->read){
            //Search first used Data Element in the direction of the write-pointer
            s_ptr = tmp_ptr;
            do{
                s_ptr = s_ptr->next;
            }while(s_ptr->data == NULL && s_ptr != rb_ptr->write);
            rb_ptr->read = s_ptr;
        }
        //Correct Write-Pointer if necessary
        if(tmp_ptr == rb_ptr->write){
            //Search first free Data Element in the direction of the write-pointer
            s_ptr = tmp_ptr;
            do{
                s_ptr = s_ptr->next;
            }while(s_ptr->data != NULL && s_ptr != rb_ptr->read);
            rb_ptr->write = s_ptr;
        }
        //Check Empty / Full Condition
        if(rb_ptr->read == rb_ptr->write){
            /***********************************************
             *next Element has data? -> Buffer must be full
             *next Element is NULL? -> Buffer must be empty
             ***********************************************/
             if(rb_ptr->read->next->data != NULL){
                 if(bnSet(rb_ptr->rbsbfa,RB_FULL)){
                     Setb(rb_ptr->rbsbfa,RB_FULL);
                 }
             }else{
                 if(bnSet(rb_ptr->rbsbfa,RB_EMPTY)){
                     Setb(rb_ptr->rbsbfa,RB_EMPTY);
                 }
             }
        }
        //Check Normal / Overflow Condition
        if(rb_ptr->read > rb_ptr->write || bSet(rb_ptr->rbsbfa,RB_FULL)){
            Setb(rb_ptr->rbsbfa,RB_OVERFLOW);
        }else{
            if(rb_ptr->read < rb_ptr->write || bSet(rb_ptr->rbsbfa,RB_EMPTY)){
                Clearb(rb_ptr->rbsbfa,RB_OVERFLOW);
            }
        }
        //Check NULL Condition
        if(bSet(rb_ptr->rbsbfa,RB_EMPTY) && rb_ptr->count_e == 0){
            bSet(rb_ptr->rbsbfa,RB_NULL);
            bClear(rb_ptr->rbsbfa,RB_EMPTY);
        }
    }
    return;
}

/** Search for a single Element in the Ringbuffer-List
 *
 */
RB_DATATYPE* find_elem(RB_DATATYPE e)
{
    RB_Elem *tmp_ptr = rb_ptr->base;
    //Buffer not Empty
    if(bnSET(rb_ptr->rbsbfa,RB_EMPTY)){
        //Until basepointer is reached again
        do{
            //Stop if found
            if( *(tmp_ptr->data) == e ){
                break;
            }
            tmp_ptr =  tmp_ptr->next;
        }while( tmp_ptr->next != rb_ptr->base );
    }
    return tmp_ptr;
}

/** Count all Elements of the given data content
 *
 */
uint32_t count_elem(RB_DATATYPE e)
{
    uint32_t count = 0;
    RB_Elem *tmp_ptr = rb_ptr->base;
    //Buffer not Empty
    if(bnSET(rb_ptr->rbsbfa,RB_EMPTY)){
        //Until basepointer is reached again
        do{
            //Count equal Elements
            if( *(tmp_ptr->data) == e ){
                ++count;
            }
            tmp_ptr =  tmp_ptr->next;
        }while( tmp_ptr->next != rb_ptr->base );
    }
    return count;
}

//*****

/** Fetch Data of one Element from the buffer
 *
 */
RB_DATATYPE get_elem(uint32_t nr)
{
    uint32_t ii;
    RB_DATATYPE res;
    RB_Elem *tmp_ptr = rb_ptr->base;
    for(ii=nr; ii>=0; ii--){
        tmp_ptr =  tmp_ptr->next;
    }
    res = tmp_ptr->data;
    return res;
}

/** Delete (first/all) Elements with Data X from Buffer
 *
 */
void del_elem(RB_DATATYPE e,uint8_t mode)
{
    RB_Elem *tmp_ptr = rb_ptr->base;
    RB_Elem *x_ptr;
    if(rb_ptr->rbsbfa != RB_EMPTY){
        switch(mode){
        case 1:
            //if mode=1 continue till end of buffer and delete all equal elements
            while( tmp_ptr->next != rb_ptr->base ){
                //find nextElement
                while( (tmp_ptr->data != e) && (tmp_ptr->next != rb_ptr->base) ){
                    tmp_ptr =  tmp_ptr->next;
                }

                if(tmp_ptr->data == e){
                    //Close Gap in Chain of Elements
                    x_ptr = tmp_ptr->previous;
                    x_ptr->next = tmp_ptr->next;
                    x_ptr = x_ptr->next;
                    x_ptr->previous = tmp_ptr->previous;

                    free(tmp_ptr);
                }
            }
            break;
        default:
            //find nextElement
            while( (tmp_ptr->data != e) && (tmp_ptr->next != rb_ptr->base) ){
                tmp_ptr =  tmp_ptr->next;
            }

            if(tmp_ptr->data == e){
                //Close Gap in Chain of Elements
                x_ptr = tmp_ptr->previous;
                x_ptr->next = tmp_ptr->next;
                x_ptr = x_ptr->next;
                x_ptr->previous = tmp_ptr->previous;

                free(tmp_ptr);
            }
            break;
        }//end-SWITCH
    }//end-IF
}

