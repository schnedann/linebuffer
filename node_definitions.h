#ifndef NODE_DEFINITIONS_H
#define NODE_DEFINITIONS_H

#include <memory>
#include <utility>

#include "iterators.h"

namespace Datastructures{

namespace Nodes {

template<typename T> using owning_ptr_t = std::unique_ptr<T>;
template<typename T> using weak_ptr_t = Core::Container::iterator_t<T>;

template<typename T> struct single_linked_single_owned{
  owning_ptr_t<T> data{};
  owning_ptr_t<single_linked_single_owned> next{nullptr};

  /*static std::unique_ptr<T> create(){
    return std::make_unique<single_linked_single_owned<T>>();
  }*/
};

template<typename T> struct double_linked_single_owned{
  owning_ptr_t<T> data{};
  owning_ptr_t<double_linked_single_owned> next{nullptr};
  weak_ptr_t<double_linked_single_owned>   prev{nullptr};

  /*static std::unique_ptr<T> create(){
    return std::make_unique<double_linked_single_owned<T>>();
  }*/
};

template<typename T> struct tree_linked_double_owned{
  owning_ptr_t<T> data{};
  owning_ptr_t<tree_linked_double_owned> left{nullptr};
  owning_ptr_t<tree_linked_double_owned> right{nullptr};

  /*static std::unique_ptr<T> create(){
    return std::make_unique<tree_linked_double_owned<T>>();
  }*/
};

} //namespace

} //namespace

#endif // NODE_DEFINITIONS_H
