#ifndef MEMBUDDY_H
#define MEMBUDDY_H

#include <cstdlib>
#include <vector>
#include <map>

#include "typesnmacros.h"

class mem_node{
private:
  u32 _size;
  bool _used;
  u32 _id;
  mem_node* _left;
  mem_node* _right;
public:
  mem_node(u32 const& psize);
  ~mem_node();
  u32 size();
  mem_node* left();
  mem_node* right();
  void setused(bool const& _u);
  mem_node* create_left(u32 const& psize);
  mem_node* create_right(u32 const& psize);
};

class membuddy{
private:
  static u32 nextpow2(u32 const& _x);
  mem_node* base;
  u32 idgen;
  std::map<u32,mem_node*> memmap;
public:
  membuddy();
  membuddy(u32 const& size);
  virtual ~membuddy();

  bool request(u32 const& size);
  u32 getblock(u32 const& size);
  bool freeblock(u32 const& id);
};

#endif // MEMBUDDY_H
