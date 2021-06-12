/**************************************************
 * Disposable single linked List
 *
 * A simple Linked List of Elements, which frees
 * the used memory as soon it gets out of scope
 *
 * implemented by Danny Schneider, 2019-2021
 **************************************************/

#ifndef DIS_SLL_H
#define DIS_SLL_H

#include <memory>
#include <utility>

#include "dtypes.h"
#include "error_mgnt.h"

namespace Datastructures{

namespace Disposable_SLL_Impl{

  /**
   * Element of single-linked list
   */
  template<typename T> struct dis_sll_elem{
    T data;
    //the unique_ptr will automaticly dispose further elements when it gets out of scope
    std::unique_ptr<dis_sll_elem<T>> next;
  };

} //namespace

template<typename T> class dis_sll{
private:

  //the unique_ptr will automaticly dispose further elements when it gets out of scope
  std::unique_ptr<Disposable_SLL_Impl::dis_sll_elem<T>> base;

public:

  dis_sll()=default;
  ~dis_sll()=default;

  //---

  /**
   * @brief add - Add new Element
   * @param _d
   */
  void add(T const& _d){
    if(!base){
      base = std::unique_ptr<Disposable_SLL_Impl::dis_sll_elem<T>>(new Disposable_SLL_Impl::dis_sll_elem<T>());
      base->data = _d;
    }else{
      auto cptr = base.get();
      auto nptr = cptr->next.get();
      while(nullptr!=nptr){
        cptr=nptr;
        nptr = cptr->next.get();
      }
      cptr->next = std::unique_ptr<Disposable_SLL_Impl::dis_sll_elem<T>>(new Disposable_SLL_Impl::dis_sll_elem<T>());
      cptr->next->data = _d;
    }
    return;
  }

  /**
   * @brief next - Traverse through elements of lists
   * @param rewind - at the first execution we need to reset Traversal of the list
   * @return true on first item indicates an error,
   *         which means two things, a.) no further
   *         elements in the list and b.) the second
   *         item must not be accessed, as it is invalid
   */
  Core::Flow::with_error_t<T> next(bool rewind){
    auto res = Core::Flow::make_with_error(T(),true);
    static Disposable_SLL_Impl::dis_sll_elem<T>* cptr = nullptr; //Mind the static
    if(base){
      if(rewind){
        cptr = base.get();
      }
      if(cptr!=nullptr){
        res.first  = false;
        res.second = cptr->data;
        cptr = cptr->next.get();
      }
    }
    return res;
  }
};

} //namespace

#endif // DIS_SLL_H
