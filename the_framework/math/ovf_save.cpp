#include "ovf_save.h"

Math::OverflowSafe::ovf_save::ovf_save():overflow(false)
{
}

auto Math::OverflowSafe::ovf_save::get_of()->bool{
  return overflow;
}
