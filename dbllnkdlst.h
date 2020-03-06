#ifndef DBLLNKDLST_H
#define DBLLNKDLST_H

#include "node_definitions.h"

namespace Datastructures{

template<typename T> class dbllnkdlst{
public:
  using own_ptr_t = Datastructures::Nodes::owning_ptr_t<Datastructures::Nodes::double_linked_single_owned<T>>;
  using wk_ptr_t  = Datastructures::Nodes::weak_ptr_t<Datastructures::Nodes::double_linked_single_owned<T>>;
private:
  own_ptr_t base{nullptr};
  wk_ptr_t  top{nullptr};
public:
   dbllnkdlst()=default;
  ~dbllnkdlst()=default;

  void push_front(T const& _d){
    if(!base){
      //List Empty
      base = std::make_unique<Datastructures::Nodes::double_linked_single_owned<T>>();
      //Set Top
      top = base.get();
    }else{
      auto tmp = std::make_unique<Datastructures::Nodes::double_linked_single_owned<T>>();
      //Whereever base-prev was pointing to, we will copy that as the new base
      tmp->prev = base->prev;
      //Set base->prev, as tmp will go in front of current base
      base->prev = tmp.get();
      //we now shift current base behind the new element
      tmp->next = std::move(base);
      //transfer ownership of tmp to base
      base = std::move(tmp);
    }
    base->data = std::make_unique<T>();
    *(base->data.get()) = _d;
    return;
  }

  void push_back(T const& _d){
    //if(Core::Container::is_valid(top)){
    if(!base){
      //List Empty
      base = std::make_unique<Datastructures::Nodes::double_linked_single_owned<T>>();
      //Set Top
      top = base.get();
    }else{
      auto tmp = std::make_unique<Datastructures::Nodes::double_linked_single_owned<T>>();
      //if tmp is chained behind current top, we need to point back to top
      tmp->prev = top;
      //transfer ownership of tmp to top
      top->next = std::move(tmp);
      //top still points on the old node, so correct that
      top = top->next.get();
    }
    top->data = std::make_unique<T>();
    *(top->data.get()) = _d;
    return;
  }

  size_t count(wk_ptr_t const& first, wk_ptr_t const& last){
    size_t cnt = 0;
    bool OK  = Core::Container::is_valid(first);
         OK &= Core::Container::is_valid(last);
    if(OK){
      for(wk_ptr_t ptr=first; ptr!=last->next.get(); ptr=ptr->next.get()){
        ++cnt;
      }
    }
    return cnt;
  }

  size_t count(){
    return count(base.get(),top);
  }

};

} //namespace

#endif // DBLLNKDLST_H
