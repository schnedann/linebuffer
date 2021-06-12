#ifndef GENERIC_CALC_H
#define GENERIC_CALC_H

#include "dtypes.h"
#include "para_crc.h"      //CRC Algo Parameter Sets
#include "base_crc.h"      //CRC Class Template
#include "parallel_crc.h"  //parallel Style Algorithms
#include "table_crc.h"     //table    Style Algorithms

namespace crc
{
  
class generic_crc : public base_crc
{
private:
  u64 data_width;

  table_crc    tcrc; //Instance for Table    Style CRC Algorithms
  parallel_crc pcrc; //Instance for Parallel Style CRC Algorithms
  
public:
	generic_crc();
	virtual ~generic_crc();

  void set_para(crc_para_t const& ps);
  void setup(u64 const& dw);
  void init_crc();
  void crc_calc(u8 const& data);
  u64 get_crc();
  
  u64& get_crc_reg();
  crc_para_t& get_para();
  void operator=(base_crc& bc);
};

} //namespace

#endif // BASE_CALC_H
