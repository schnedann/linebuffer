#include "intmacros.h"
#include "generic_crc.h"

namespace crc
{

generic_crc::generic_crc()
{
  return;
}

generic_crc::~generic_crc()
{
  return;
}

//-----

  /**
   * @brief Overload Base-Class: Set fixed CRC Parameters
   * @param ps
   */
  void generic_crc::set_para(crc_para_t const& ps){
    para_set = ps;
    return;
  }

  /**
   * @brief Setup variable Parameters
   * @param dw
   */
  void generic_crc::setup(u64 const& dw){
    data_width = dw;
    return;
  }
  
  /**
   * @brief Overload Base-Class: Preload CRC Register with initial value
   */
  void generic_crc::init_crc(){
    crc_reg = para_set.crc_init; 
    return;
  }

  /**
   * @brief Overload Base-Class: Execute Calculation with given CRC Mode
   * @param data
   */
  void generic_crc::crc_calc(u8 const& data){
    u16 mode = para_set.crc_mode & CRC_MODE_MASK;
     
    switch(mode){
    case CRC_MODE_SERIAL:{
      break;
    } 
    case CRC_MODE_PALGO1:{
      pcrc = *this;         //Copy CRC Calculation State
      pcrc.crc_calc(data);
      *this = pcrc;         //Copy CRC Calculation State
      break;
    }
    case CRC_MODE_PALGO2:{
      pcrc = *this;         //Copy CRC Calculation State
      pcrc.crc_calc(data);
      *this = pcrc;         //Copy CRC Calculation State
      break;
    }
    case CRC_MODE_PALGO3:{
      pcrc = *this;         //Copy CRC Calculation State
      pcrc.crc_calc(data);
      *this = pcrc;         //Copy CRC Calculation State
      break;
    }
    case CRC_MODE_TALGO1:{
      tcrc = *this;         //Copy CRC Calculation State
      tcrc.crc_calc(data);
      *this = tcrc;         //Copy CRC Calculation State
      break;
    }
    };
    return;
  }

  /**
   * @brief Overload Base-Class: Retrieve CRC Result with Final XOR and/or Bitreverse if configured
   * @return
   */
  u64  generic_crc::get_crc(){
    u64 res =  crc_reg ^= para_set.fxor;
		return (para_set.crc_mode & CRC_MODE_REVOUT)?(bitreverse(res,para_set.crc_width)):(res);
  }

//----- Class Assignment Operator

  /**
   * @brief Overload Base-Class:
   * @return
   */
	u64& generic_crc::get_crc_reg(){
    return crc_reg;
  }
  
	/**
	 * @brief Overload Base-Class:
	 * @return
	 */
  crc_para_t& generic_crc::get_para(){
    return para_set;
  }

	/**
	 * @brief Overload Base-Class: Copy internal State between CRC Algorithm Types
   *                             Allows to use different Algorithms for the same
   *                             Task: e.g. Execute a 9bit crc with a 8bit table
   *                             plus a 1bit serial style Algorithm
	 * @param bc
	 */
  void generic_crc::operator=(base_crc& bc){
    para_set = bc.get_para();
    crc_reg  = bc.get_crc_reg();  
  }	  

//-----
  
} //namespace
