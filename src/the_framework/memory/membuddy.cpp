#include "membuddy.h"


membuddy::membuddy():base(nullptr),idgen(0){
  return;
}

membuddy::membuddy(const u32 &size):base(nullptr),idgen(0){
  if(size > 0){
    base = new mem_node(nextpow2(size));
  }
  return;
}

membuddy::~membuddy(){
  if(base!=nullptr) delete base;
  return;
}

u32 membuddy::nextpow2(u32 const& _x){
  u32 lx = _x;
  --lx;
  lx |= lx >> 1;
  lx |= lx >> 2;
  lx |= lx >> 4;
  lx |= lx >> 8;
  lx |= lx >> 16;
  ++lx;
  return lx;
}

bool membuddy::request(u32 const& size){
  bool res = false;

  mem_node* ptr = base;

  if(ptr->size() > size){
    if(((ptr->size())>>1) > size){
      if(ptr->left()!=nullptr){
        ptr=ptr->left();
      }else{

      }

    }else{

    }

  }

  return res;
}

u32 membuddy::getblock(u32 const& size){
  u32 res = idgen++;

  return res;
}

bool membuddy::freeblock(u32 const& id){
  bool res = false;
  mem_node* ptr = memmap.at(id);
  if(ptr->left()==nullptr && ptr->right()==nullptr){
    ptr->setused(false);
    memmap.erase(id);
  }
  return res;
}

//-----

mem_node::mem_node(const u32 & psize):_size(psize),_used(false),_left(nullptr),_right(nullptr){
  return;
}

mem_node::~mem_node(){
  if(_right!=nullptr) delete _right;
  if(_left!=nullptr) delete _left;
  return;
}

u32 mem_node::size()
{
  return _size;
}

mem_node *mem_node::left()
{
  return _left;
}

mem_node *mem_node::right()
{
  return _right;
}

void mem_node::setused(const bool &_u)
{
  _used = _u;
  return;
}

mem_node *mem_node::create_left(u32 const& psize)
{
  if(_left!=nullptr) _left = new mem_node(psize);
  return _left;
}

mem_node *mem_node::create_right(u32 const& psize)
{
  if(_right!=nullptr) _right = new mem_node(psize);
  return _right;
}
