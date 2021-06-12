/***************************************************
 * Array based Ringbuffer [FiFo]
 * by Danny Schneider, July 2010-2021
 ***************************************************/

/*
Copyright (c) 2010-2021, Danny Schneider
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Neither the name of the original Author nor the
      names of its contributors may be used to endorse or promote products
      derived from this software without specific prior written permission.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
(INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
(INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef RINGBUFFER_H
#define RINGBUFFER_H

//----- System-Includes

#include <cassert>
#include <array>

//----- Includes

#include "dtypes.h"
#include "bitmacros.h"
#include "compile_guards.h"
#include "iterators.h"
#include "fastcopy.h"

namespace Datastructures{

template<typename T, typename I, I N> class ringbuffer{

private:

  constexpr static I const crb_OVERFLOW  = Math::Boolean::MASK_MSB<T>();
  constexpr static I const crb_TYPEBYTES = (crb_OVERFLOW-1);

  std::array<T,N> buffer{}; //Array of arbitrary Type
  I ri{0};     //Read Index
  I wi{0};     //Write Index
  bool overflow{false};

  void typecheck(){
    Compile::Guards::IsUnsigned<I>();
    return;
  }

public:
  ringbuffer()=default;
  ringbuffer(ringbuffer const&)=delete;
  ringbuffer(ringbuffer&&)=delete;
  ~ringbuffer()=default;

  //-----

  using rb_data_t = Core::Container::iterator_t<T>;

  //----- Stack Access [Push & Pop]

  /**
   * Transfer new Data to the Buffer
   * buff - Buffer Ctrl Structure
   * ptr  - Pointer to Buffer Data Source
   */
  void push(rb_data_t s_ptr){
    if(free()>0){ //free Elements in Buffer?
      //Copy Data

      if(Core::Container::is_valid<T>(s_ptr)){
        auto t_ptr = Core::Container::advance<T>(buffer.data(),wi);
        Algorithms::fastcopy<T>(s_ptr,t_ptr,1); //Copy single Element
      }
      //Move Write Pointer
      ++(wi);
      //Warp Index
      if(wi == N){
          wi = 0;
      }
      //Overflow
      if(!overflow){ //no Overflow yet?
        if(wi <= ri){
          overflow=true; //set Overflow
        }
      }
  //---
    }
    return;
  }

  /**
   * Execute a Push without Copy any Data to the Buffer
   * Return a Index of the Element, so a external Process can
   * Copy the Data to the Buffer
   * So you can copy Data to the Buffer[Memory] from some not Memory-Mapped
   * Pheriphial e.g a HW-Fifo of some communication device
   */
  u16 pseudopush(){
    u16 res = wi;  //get current write Index
    push(nullptr); //push without data
    return res;
  }

  /**
   * Undo last Push
   * Restore the Write Pointer
   * In Case Data was overwritten => its LOST!
   */
  void undopush(){
    pop(nullptr);
    return;
  }

  /**
   * Transfer Data from the Buffer
   * buff - Buffer Ctrl Structure
   * ptr  - Pointer to Buffer Data Target
   */
  void pop(rb_data_t t_ptr){
    //used Elements in Buffer
    if(free()<N){
      if(Core::Container::is_valid<T>(t_ptr)){
        auto s_ptr = Core::Container::advance<T>(buffer.data(),ri);
        Algorithms::fastcopy(s_ptr,t_ptr,sizeof(T));
      }
      //Move Read Pointer
      ++(ri);
      //Warp Index
      if(ri == N){
        ri = 0;
      }
      //Overflow
      if(overflow){
        if(ri <= wi){
          overflow=false; //Reset Overflow
        }
      }
    }
    return;
  }

  //----- get Stack Status

  /**
   * Get Number of Free Elements in the buffer
   * buff - Buffer Ctrl Structure
   */
  u16 free(){
    u16 res = 0;
    if(overflow){
      res = ri - wi;
    }else{
      res = N - (wi - ri);
    }
  #ifdef _DEBUG
    printf("Free: %u\n",res);
  #endif
   return res;
  }

  //----- Access to Stack Data [so the stack data can be processed as normal Array]

  /**
   * Throw away all data, buffer is empty
   * and ready to receive more Data
   * buff - Buffer Ctrl Structure
   */
  void flush(){
    for(auto& _x:buffer){
      _x = T();
    }
    wi = 0;
    ri = 0;
    overflow = false;
    return;
  }

  /**
   * Get Access-Pointer to Data Array
   * buff - Buffer Ctrl Structure
   */
  rb_data_t data(){
    return buffer.data();
  }

  bool full(){
    return (0==free());
  }

  bool empty(){
    return (N==free());
  }

  I size(){
    return N;
  }

  struct status{
    I write;
    I read;
  };
  struct status get_status(){
    return {wi,ri};
  }
};

} //namespace

//-----

#endif //ARRAY_RINGBUF_H
