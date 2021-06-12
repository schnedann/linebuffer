//#include <iostream>
#include <iomanip>
#include <sstream>
#include <cmath>

#include "intmacros.h"
#include "stringfkt.h"
#include "table_crc.h"
#include "parallel_crc.h"

using namespace std;

namespace crc
{

table_crc::table_crc()
{
  return;
}

table_crc::~table_crc()
{
  return;
}

  /**
   *
   */
  void table_crc::set_para(crc_para_t const& ps){
    para_set = ps;
    return;
  }

  /**
   *
   */
  void table_crc::init_crc(){
    crc_reg = para_set.crc_init;
    return;
  }

  /**
   * CRC Lookup Table Calculation
   */
  void table_crc::calc_table(){
		parallel_crc pcrc;

    //Copy Para-Set with Poly
    crc_para_t ppara = para_set;
    ppara.crc_init = 0; //Init with Zero
    ppara.crc_mode = 0; //Reverse of In or Out
    ppara.fxor     = 0; //No Final XOR
    pcrc.set_para(ppara);

    //cout << ppara.listpara() << endl;

    for(u64 ii=0; ii<dBITSPACE(para_set.data_width); ++ii){
			pcrc.init_crc();
			pcrc.crc_calc((u8)(ii&255));
      crc_tab.push_back(pcrc.get_crc());
    }
    return;
  }

  /**
   * CRC Lookup Table to String
   */
  string table_crc::print_table(){
		stringstream ss;
    u64 index = 0;
    u64 dwidth = std::ceil(std::log10(dBITSPACE(para_set.data_width)));
    u64 cwidth = std::ceil(std::log10(dBITSPACE(para_set.crc_width)));
    u64 cwidthhex = std::ceil(std::log(dBITSPACE(para_set.crc_width))/std::log(16));
		ss << "Table-Size: " << crc_tab.size() << endl;
		for(u64 entry:crc_tab){
			ss << setw(dwidth) << dec << index++ << ": " << stdext::stringfkt::prnbin(entry,para_set.crc_width) << " --> " << setw(cwidth) << entry << " --> " << setw(cwidthhex) << setfill('0') << hex << entry << endl;
		}
    return ss.str();
  }
	
  /**
   *
   */
  void table_crc::crc_calc(u8 const& data){
    //Local Copy of Data
    u8 ldata = (para_set.crc_mode & CRC_MODE_REV_IN)?(bitreverse(data,para_set.data_width)):(data);
    u64 tmp = crc_reg>>(para_set.crc_width-para_set.data_width);
    tmp ^= ldata;
    crc_reg <<= para_set.data_width;
    crc_reg ^= crc_tab[tmp];
    crc_reg &= dOFS_MAX(para_set.crc_width);
    return;
  }

  /**
   *
   */
  u64 table_crc::get_crc(){
    u64 res =  crc_reg ^= para_set.fxor;
		return (para_set.crc_mode & CRC_MODE_REVOUT)?(bitreverse(res,para_set.crc_width)):(res);
  }

//----- Class Assignment Operator

  /**
	 *
	 */
	u64& table_crc::get_crc_reg(){
    return crc_reg;
  }
  
	/**
	 *
	 */
  crc_para_t& table_crc::get_para(){
    return para_set;
  }

	/**
	 * Copy internal State betwenn CRC Types
	 */
  void table_crc::operator=(base_crc& bc){
    para_set = bc.get_para();
    crc_reg  = bc.get_crc_reg();  
  }	  

//-----

} //namespace
