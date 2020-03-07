#ifndef DBLLNKDLST_H
#define DBLLNKDLST_H

#include <functional>

#include "dtypes.h"
#include "iterators.h"
#include "node_definitions.h"

namespace Datastructures{

template<typename T> class dbllnkdlst{
public:
  using data_t    = Core::Container::owning_ptr_t<T>;
  using wk_data_t = Core::Container::weak_ptr_t<T>;
  using own_ptr_t = Core::Container::owning_ptr_t<Datastructures::Nodes::double_linked_single_owned<T>>;
  using wk_ptr_t  = Core::Container::weak_ptr_t<Datastructures::Nodes::double_linked_single_owned<T>>;
private:
  own_ptr_t base{nullptr};
  wk_ptr_t  top{nullptr};
public:
   dbllnkdlst()=default;
  ~dbllnkdlst()=default;

  //----- Push to List

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

  //----- Pop from List

  data_t pop_front(){
    data_t res{nullptr};
    if(base){
      res = std::move(base->data);
      bool more = base->next.operator bool();
      if(more){
        base->next->prev = base->prev;
        base = std::move(base->next);
      }else{
        base = nullptr;
        top = nullptr;
      }
    }
    return res;
  }

  data_t pop_back(){
    data_t res{nullptr};
    if(base){
      res = std::move(top->data);
      bool more = base->next.operator bool();
      if(more){
        top = top->prev;
        top->next.reset();
      }else{
        base = nullptr;
        top = nullptr;
      }
    }
    return res;
  }

  //-----

  /*T& operator[](size_t idx){
    return;
  }
  const T& operator[](size_t idx) const{
    return;
  }*/

  //----- Traversing List

  wk_ptr_t get_next(wk_ptr_t const& start) const{
    wk_ptr_t ptr{nullptr};
    if(Core::Container::is_valid(start)){
      ptr = start->next.get();
    }else{
      ptr = base.get();
    }
    return ptr;
  }

  wk_ptr_t get_prev(wk_ptr_t const& start) const{
    wk_ptr_t ptr{nullptr};
    if(Core::Container::is_valid(start)){
      ptr = start->prev;
    }else{
      ptr = top;
    }
    return ptr;
  }

};

//-----

template<typename T> with_error_t<typename dbllnkdlst<T>::wk_ptr_t> get_node(dbllnkdlst<T> const& dll, size_t const idx){
  bool err = true;
  typename dbllnkdlst<T>::wk_ptr_t ptr = nullptr;
  typename dbllnkdlst<T>::wk_ptr_t it = dll.get_next(nullptr);

  size_t cnt = 0;
  while(Core::Container::is_valid(it) && cnt<idx){
    it = dll.get_next(it);
    ++cnt;
  }
  err = !(cnt==idx);
  if(!err) ptr = it;
  return make_with_error<typename dbllnkdlst<T>::wk_ptr_t>(err,ptr);
}

//-----

template<typename T> with_error_t<typename dbllnkdlst<T>::wk_data_t> at(dbllnkdlst<T> const& dll, size_t const idx){
  bool err = true;
  typename dbllnkdlst<T>::wk_data_t ptr = nullptr;
  typename dbllnkdlst<T>::wk_ptr_t it = dll.get_next(nullptr);
  size_t cnt = 0;
  while(Core::Container::is_valid(it) && cnt<idx){
    it = dll.get_next(it);
    ++cnt;
  }
  err = !(cnt==idx);
  if(!err) ptr = it->data.get();
  return make_with_error<typename dbllnkdlst<T>::wk_data_t>(err,ptr);
}

//----- Count Elements

template<typename T> size_t count(typename dbllnkdlst<T>::wk_ptr_t const& first, typename dbllnkdlst<T>::wk_ptr_t const& last){
  size_t cnt = 0;
  bool OK  = Core::Container::is_valid(first);
       OK &= Core::Container::is_valid(last);
  if(OK){
    for(typename dbllnkdlst<T>::wk_ptr_t ptr=first; ptr!=last->next.get(); ptr=ptr->next.get()){
      ++cnt;
    }
  }
  return cnt;
}

template<typename T> size_t count(dbllnkdlst<T> const& dll){
  return count<T>(dll.get_next(nullptr),dll.get_prev(nullptr));
}

//-----

template<typename T> with_error_t<size_t> find_match(dbllnkdlst<T> const& dll, std::function<bool(T const&)> fct){
  bool found = false;
  size_t idx = 0;
  if(fct){
    for(auto ptr = dll.get_next(nullptr); ptr!=nullptr; ptr = dll.get_next(ptr)){
      found = fct(*(ptr->data.get()));
      if(found) break;
      ++idx;
    }
  }
  return make_with_error<size_t>(!found,idx);
}

template<typename T> with_error_t<size_t> rfind_match(dbllnkdlst<T> const& dll, std::function<bool(T const&)> fct){
  bool found = false;
  size_t idx = count(dll);
  if(fct && (idx>0)){
    for(auto ptr = dll.get_prev(nullptr); ptr!=nullptr; ptr = dll.get_prev(ptr)){
      found = fct(*(ptr->data.get()));
      --idx;
      if(found) break;
    }
  }
  return make_with_error<size_t>(!found,idx);
}

//-----

template<typename T> void for_each_node(dbllnkdlst<T> const& dll, std::function<void(typename Datastructures::dbllnkdlst<T>::wk_data_t dptr)> fct){
  if(fct){
    for(auto ptr = dll.get_next(nullptr); ptr!=nullptr; ptr = dll.get_next(ptr)){
      fct(ptr->data.get());
    }
  }
  return;
}

//-----

} //namespace

#endif // DBLLNKDLST_H
