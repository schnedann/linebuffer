#include <iomanip>

#include "para_crc.h"
#include "Stringhelper.h"
#include "math_discrete.h"

Algorithms::CRC::crc_para_t crc_para_init = {
  "",0,0,0,0,0,0,0
};

/**
 * @brief Method for Printing a Brief about a supplied Set of CRC Parametes
 * @param cp
 * @return
 */
std::string Algorithms::CRC::crc_para::listpara(Algorithms::CRC::crc_para_t const& cp){
  std::string res;
  std::stringstream ss;
  auto const line = Utility::Strings::Smply("=",50);
  ss << line << std::endl;
  ss << cp.name << std::endl;
  ss << " CRC-Bits:         " << std::dec << std::setw(4) << (u64)(cp.crc_width)  << std::endl;
  ss << "Data-Bits:         " << std::dec << std::setw(4) << (u64)(cp.data_width) << std::endl;
  ss << "Init:              0x" << std::setfill('0') << std::setw(Math::Discrete::nextpow2<u8>((cp.crc_width)>>2)) << std::hex << cp.crc_init << "u" << std::endl;
  ss << "Poly:              0x" << std::setfill('0') << std::setw(Math::Discrete::nextpow2<u8>((cp.crc_width)>>2)) << std::hex << cp.crc_poly << "u" << std::endl;
  ss << "FXor:              0x" << std::setfill('0') << std::setw(Math::Discrete::nextpow2<u8>((cp.crc_width)>>2)) << std::hex << cp.fxor     << "u" << std::endl;
  ss << "Expected Result:   0x" << std::setfill('0') << std::setw(Math::Discrete::nextpow2<u8>((cp.crc_width)>>2)) << std::hex << cp.eresult  << "u" << std::endl;
  ss << line << std::endl;
  res = ss.str();
  return res;
}
