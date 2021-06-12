#ifndef PARALLEL_CRC_H
#define PARALLEL_CRC_H

#include "dtypes.h"
#include "para_crc.h"
#include "base_crc.h"

namespace crc
{

class parallel_crc : public base_crc
{
private:
  void crc_calc_v1(u8 const& data);
  void crc_calc_v2(u8 const& data);
  void crc_calc_v3(u8 const& data);
public:
  parallel_crc();
  ~parallel_crc();

  void set_para(crc_para_t const& ps);
  void init_crc();
  void crc_calc(u8 const& data);
  u64 get_crc();
  
  u64& get_crc_reg();
  crc_para_t& get_para();
  void operator=(base_crc& bc);
  
};

}

#endif // PARALLEL_CRC_H
