#ifndef PARA_CRC_SETS_H_
#define PARA_CRC_SETS_H_

#include  <array>
#include "para_crc.h"

/**
 * Predefined Parameter Sets
 * for known CRC Polynoms
 */
//-----  5 Bit
#define SET_CRC5USB          0
//-----  6 Bit
#define SET_CRC6CDMA2000A    1
//-----  8 Bit
#define SET_CRC8             2
#define SET_CRC8DVBS2        3
#define SET_CRC8ITU          4
//----- 15 Bit
#define SET_CRC15_CAN2       5
//----- 16 Bit
#define SET_CRC16_AUGCCITT   6
#define SET_CRC16_BUYPASS    7
//----- 31 Bit
#define SET_CRC31PHILIPS     8
//----- 32 Bit
#define SET_CRC32            9
#define SET_CRC32BZIP2      10
#define SET_CRC32MPEG2      11
//----- 40 Bit
#define SET_CRC40GSM        12
//----- 64 Bit
#define SET_CRC64           13
#define SET_CRC64XZ         14
//----- END of List
#define SET_CRC_ELEMENTS    15

namespace Algorithms {

namespace CRC {

extern std::array<Algorithms::CRC::crc_para_t,SET_CRC_ELEMENTS> crc_para_sets;

} //namespace

} //namespace

#endif
