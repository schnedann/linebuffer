#ifndef _CRC_ALGORITHM_H_
#define _CRC_ALGORITHM_H_

#include "dtypes.h"

#define STD_CRC_ALGO_CRC32          0
#define STD_CRC_ALGO_CRC_8          1
#define STD_CRC_ALGO_CRC_8_CDMA2000 2
#define STD_CRC_ALGO_CRC_8_DVB_S2   3

typedef struct crc_algo_para_st{
  u8  dwidth;       //Data Bitwidth
  u8  pwidth;       //Poly Bitwidth
  bool ref_data;    //Reflect Data
  bool ref_result;  //Reflect Result
  bool ref_poly;    //Reflect Poly
  u64 poly;         //CRC Polynom
  u64 init;         //Init Value
  u64 fxor;         //Final XOR
}crc_algo_para_t;

class crcalgo
{
private:
  crc_algo_para_t para;
public:
  crcalgo();
  virtual ~crcalgo();

  // --- Config ---
  void setpara(crc_algo_para_t cap);
  u8  dbytes();
  u8  pbytes();
  u8  dbits();
  u8  pbits();
  u64 poly();
  u64 init();

  // --- Parallel Execuion ---

  /**
   * X Bit "parallel" Algorithm
   */
  u64 calc(u64 const&, u64 const&); //Data, Init

  // --- Serial Execuion ---

  /**
   * Single Bit Step
   */
  u64 serial_step(bool const&, u64 const&);

  // ---

  /**
   * Final Reflect / XOR
   */
  u64 getresult(u64 const&);

  /**
   * calc crc with algo-parameters of the series: 
   * {0,1,2,3,4,5,6,7,8,9}
   * and compare with known result
   */
  bool check(u64 const&);
};

extern crc_algo_para_t std_crc_algo[];

#endif // _CRC_ALGORITHM_H_
