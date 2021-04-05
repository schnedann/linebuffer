#include "endianness_detect.h"

#include <array>

/**
 * @brief Enviroment::Endianness::endianness
 * @return found Endianness
 */
Enviroment::Endianness::endianness_t Enviroment::Endianness::endianness(void){
  union{
    u32 value;
    std::array<u8,sizeof(u32)> data;
  } number;
  number.data[0] = 0x00;
  number.data[1] = 0x01;
  number.data[2] = 0x02;
  number.data[3] = 0x03;

  endianness_t res = endianness_t::ENDIAN_UNKNOWN;

  switch (number.value){
    case UINT32_C(0x00010203):{
      res = endianness_t::ENDIAN_BIG;
      break;
    }
    case UINT32_C(0x03020100):{
      res = endianness_t::ENDIAN_LITTLE;
      break;
    }
    case UINT32_C(0x02030001):{
      res = endianness_t::ENDIAN_BIG_WORD;
      break;
    }
    case UINT32_C(0x01000302):{
      res = endianness_t::ENDIAN_LITTLE_WORD;
      break;
    }
    default:{
      res = endianness_t::ENDIAN_UNKNOWN;
      break;
    }
  }
  return res;
}

/**
 * @brief Enviroment::Endianness::is_expected
 * @param endi
 * @return true if found Endianness is equal to the expected Endianness (endi)
 */
bool Enviroment::Endianness::is_expected(const Enviroment::Endianness::endianness_t endi){
  return (endi == endianness());
}
