#ifndef BASE_CRC_H
#define BASE_CRC_H

#include "dtypes.h"
#include "para_crc.h" //CRC Algo Parameter Sets

namespace Algorithms{

namespace CRC{

/**
 * Class Template for CRC Algorithms
 */
class base_crc
{
protected:
  crc_para_t para_set;
  u64 crc_reg;
public:
  base_crc():para_set(crc_para_init),crc_reg(0)
  {
    return;
  }

  virtual ~base_crc()
  {
    return;
  }

  virtual void set_para(crc_para_t const& ps) =0;
  virtual void init_crc() =0;
  virtual void crc_calc(u8 const& data) =0;
  virtual u64  get_crc() =0;

  virtual u64& get_crc_reg() =0;
  virtual crc_para_t& get_para() =0;
  virtual void operator=(base_crc& bc) =0;
};

} //namespace

} //namespace

#endif // BASE_CALC_H
