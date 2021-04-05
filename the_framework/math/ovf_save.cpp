#include "ovf_save.h"

Math::OverflowSafe::ovf_save::ovf_save():overflow(false)
{
}

bool Math::OverflowSafe::ovf_save::get_of() const{
  return overflow;
}
