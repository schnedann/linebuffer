#ifndef PARA_CRC_H_
#define PARA_CRC_H_

#include <string>
#include <sstream>

#include "dtypes.h"

namespace Algorithms{

namespace CRC{

/**
 * Reflect Input Data and/or Output CRC
 * Hint: Reflect means bitreverse !
 */
static constexpr u32 const CRC_MODE_REV_IN = 1; //Reflect Data
static constexpr u32 const CRC_MODE_REVOUT = 2; //Reflect Result

/**
 * Availible CRC Algorithms
 */
static constexpr u32 const CRC_MODE_SERIAL = 0x0000U; //Serial               --> one Bit per Call
static constexpr u32 const CRC_MODE_PALGO1 = 0x1000U; //Parallel             --> X Bits per Call, but multiple shifts
static constexpr u32 const CRC_MODE_PALGO2 = 0x2000U; //Parallel             --> X Bits per Call, but multiple shifts
static constexpr u32 const CRC_MODE_PALGO3 = 0x3000U; //Parallel             --> X Bits per Call, but multiple shifts
static constexpr u32 const CRC_MODE_TALGO1 = 0x4000U; //Table based Parallel --> X Bits per Call

static constexpr u32 const CRC_MODE_MASK = 0xF000U;


typedef struct crc_para_st{
  std::string name;
  u8  data_width;
  u8  crc_width;
  u64 crc_poly;
  u64 crc_init;
  u64 fxor;
  u16 crc_mode;
  u64 eresult;
}crc_para_t;

class crc_para{
public:
  static std::string listpara(crc_para_t const& cp);
};

extern crc_para_t crc_para_init;

} //namespace

} //namespace



#endif
