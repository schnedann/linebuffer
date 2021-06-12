#ifndef MUTAL_LOCK_H
#define MUTAL_LOCK_H

#include "dtypes.h"

namespace SYNC {

namespace LOCK {

enum class IDs_t:u8{
  ID_A = 1, //Task A
  ID_B = 2  //Task B
};

class Mutual{
private:

  volatile bool wants_to_enter_A{false};
  volatile bool wants_to_enter_B{false};
  volatile IDs_t turn{IDs_t::ID_A};

public:

  Mutual()=default;
  ~Mutual()=default;

  void wait_lock(IDs_t const id);
  bool is_locked(IDs_t const id);
  void release(IDs_t const id);
};

} //namespace

} //namespace

#endif // MUTAL_LOCK_H
