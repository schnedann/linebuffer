#ifndef TABLE_CALC_H
#define TABLE_CALC_H

#include <vector>
#include <string>

#include "dtypes.h"
#include "para_crc.h"
#include "base_crc.h"

namespace crc
{

class table_crc : public base_crc
{
private:
  std::vector<u64> crc_tab;
public:
	table_crc();
	virtual ~table_crc();

  void set_para(crc_para_t const& ps);
  void init_crc();
  void calc_table();
	std::string print_table();
  void crc_calc(u8 const& data);
  u64 get_crc();
  
  u64& get_crc_reg();
  crc_para_t& get_para();
  void operator=(base_crc& bc);
  
};

}

#endif // TABLE_CALC_H
