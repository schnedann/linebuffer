#include "parallel_crc.h"
#include "intmacros.h"

namespace crc
{  

parallel_crc::parallel_crc()
{
  return;
}

parallel_crc::~parallel_crc()
{
  return;
}

	/**
	 *
	 */
  void parallel_crc::set_para(crc_para_t const& ps){
		para_set = ps;
		return;
	}

	/**
	 *
	 */
  void parallel_crc::init_crc(){
    crc_reg = para_set.crc_init;
    return;
  }

  void parallel_crc::crc_calc(u8 const& data){
    u16 mode = para_set.crc_mode & CRC_MODE_MASK;
    switch(mode){
      case CRC_MODE_PALGO1:{
        crc_calc_v1(data);
        break;
      }
      case CRC_MODE_PALGO2:{
        crc_calc_v2(data);
        break;
      }
      case CRC_MODE_PALGO3:{
        crc_calc_v3(data);
        break;
      }
    };
		return;
  }
  
	/**
   * Blend in Data + rotate CRC Register only
   */
  void parallel_crc::crc_calc_v1(u8 const& data){
    //Local Copy of Data
    u8 ldata = (para_set.crc_mode & CRC_MODE_REV_IN)?(bitreverse(data,para_set.data_width)):(data);
    //Blend Data with CRC Register
		u64 tmp = ((u64)ldata)<<(para_set.crc_width-para_set.data_width); //shift to MSB
    crc_reg ^= tmp;                                                   //Combine
    //For all Data Bits
    for(u8 ii=0; ii<para_set.data_width; ++ii){
      //If MSB of CRC Register is '1'
      if(crc_reg & dMASK_MSB(para_set.crc_width)){
        //Shift CRC Register
        ASHIFTL(crc_reg,1);
        //XOR with Poly
        crc_reg ^= para_set.crc_poly;
      }else{
        //Only Shift CRC Register
        ASHIFTL(crc_reg,1);
      }
      //keep CRC Reg within bounds (this can be removed!)
      //Bit > MSB will be ignorded, but might confuse @ debugging
      crc_reg &= dOFS_MAX(para_set.crc_width);
		}
    return;
	}

	/**
	 * shift CRC & Data
	 */
  void parallel_crc::crc_calc_v2(u8 const& data){
    //Local Copy of Data
    u8 ldata = (para_set.crc_mode & CRC_MODE_REV_IN)?(bitreverse(data,para_set.data_width)):(data);
    //For all Data Bits
		for(u8 ii=0; ii<para_set.data_width; ++ii){
      //Get MSB of CRC Register
			bool cbit = (crc_reg&dMASK_MSB(para_set.crc_width))?(true):(false);
      //Get MSB of Data
		  bool dbit = (ldata&dMASK_MSB(para_set.data_width))?(true):(false);
      //Shift CRC Register
      ASHIFTL(crc_reg,1);
      //keep CRC Reg within bounds (this can be removed!)
      //Bit > MSB will be ignorded, but might confuse @ debugging
      crc_reg &= dOFS_MAX(para_set.crc_width);
      //if MSB's differ --> XOR Result is '1'
			if(cbit != dbit){
        //Then XOR with Poly
				crc_reg ^= para_set.crc_poly;
			}
      //Shift Data Register
      ASHIFTL(ldata,1);
		}
		return;
	}

  /**
	 *
	 */
  void parallel_crc::crc_calc_v3(u8 const& data){
    //Local Copy of Data
    u8 ldata = (para_set.crc_mode & CRC_MODE_REV_IN)?(bitreverse(data,para_set.data_width)):(data);
    //For all Data Bits
		for(u8 ii=para_set.data_width; ii>0; --ii){
      //XOR MSB's of CRC & Data
      u64 tmp_c = (crc_reg>>(para_set.crc_width-1))&1;
      u64 tmp_d = (ldata >>(ii-1))&1;
      u64 tmp = (tmp_c)^(tmp_d);
      //(always) Shift CRC Register
      ASHIFTL(crc_reg,1);
      //keep CRC Reg within bounds (this can be removed!)
      //Bit > MSB will be ignorded, but might confuse @ debugging
      crc_reg &= dOFS_MAX(para_set.crc_width);
      //if MSB's differ --> XOR Result is '1'
			if(tmp>0){
        //Then XOR with Poly
				crc_reg ^= para_set.crc_poly;
			}
		}
		return;
	}

	/**
	 * Get CRC Result (optional Final XOR)
	 */
  u64 parallel_crc::get_crc(){
    u64 res =  crc_reg ^= para_set.fxor;
		return (para_set.crc_mode & CRC_MODE_REVOUT)?(bitreverse(res,para_set.crc_width)):(res);
	}

//----- Class Assignment Operator
	
	/**
	 *
	 */
	u64& parallel_crc::get_crc_reg(){
    return crc_reg;
  }
	
	/**
	 *
	 */
  crc_para_t& parallel_crc::get_para(){
    return para_set;
  }
	
	/**
	 * Copy internal State betwenn CRC Types
	 */
  void parallel_crc::operator=(base_crc& bc){
    para_set = bc.get_para();
    crc_reg  = bc.get_crc_reg();
    return;
  }
	
//-----
	
} //namespace

