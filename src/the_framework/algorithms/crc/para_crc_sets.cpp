#include "para_crc_sets.h"

using namespace Algorithms::CRC;

/**
 * 00
 * CRC-5/USB
 * width=5 poly=0x05 init=0x1f refin=true refout=true xorout=0x1f check=0x19 name="CRC-5/USB"
 */
crc_para_t const init001 = {"CRC-5/USB",0,5,0x05,0x1FLLU,0x00LLU,(CRC_MODE_REV_IN|CRC_MODE_REVOUT),0x19LLU};

/**
 * 01
 * CRC-6/CDMA2000-A
 * width=6 poly=0x27 init=0x3f refin=false refout=false xorout=0x00 check=0x0d name="CRC-6/CDMA2000-A"
 */
crc_para_t const init002 = {"CRC-6/CDMA2000-A",0,6,0x27,0x3FLLU,0x00LLU,(CRC_MODE_REV_IN|CRC_MODE_REVOUT),0x0DLLU};

/**
 * 02
 * CRC-8
 * width=8 poly=0x07 init=0x00 refin=false refout=false xorout=0x00 check=0xf4 name="CRC-8
 */
crc_para_t const init003 = {"CRC8",0,8,0x07,0x00LLU,0x00LLU,0,0xF4LLU};

/**
 * 03
 * CRC-8/DVB-S2
 * width=8 poly=0xd5 init=0x00 refin=false refout=false xorout=0x00 check=0xbc name="CRC-8/DVB-S2"
 */
crc_para_t const init004 = {"CRC-8/DVB-S2",0,8,0xD5,0x00LLU,0x00LLU,0,0xBCLLU};

/**
 * 04
 * CRC-8/ITU
 * width=8 poly=0x07 init=0x00 refin=false refout=false xorout=0x55 check=0xa1 name="CRC-8/ITU"
 */
crc_para_t const init005 = {"CRC-8/ITU",0,8,0x07LLU,0x00LLU,0x55LLU,0,0xA1LLU};

/**
 * 05
 * CRC-15(CAN2.0)
 * width=15 poly=0x4599 init=0x0000 refin=false refout=false xorout=0x0000 check=0x059e name="CRC-15(CAN2.0)"
 */
crc_para_t const init006 = {"CRC-15(CAN2.0)",0,15,0x4599LLU,0x0000LLU,0x0000LLU,0,0x059ELLU};

/**
 * 06
 * CRC-16/AUG-CCITT
 * width=16 poly=0x1021 init=0x1d0f refin=false refout=false xorout=0x0000 check=0xe5cc
 */
crc_para_t const init007 = {"CRC-16/AUG-CCITT",0,16,0x1021LLU,0x1D0FLLU,0x0000LLU,0,0xE5CCLLU};

/**
 * 07
 * CRC-16/BUYPASS
 * width=16 poly=0x8005 init=0x0000 refin=false refout=false xorout=0x0000 check=0xfee8
 */
crc_para_t const init008 = {"CRC-16/BUYPASS",0,16,0x8005LLU,0x0000LLU,0x0000LLU,0,0xFEE8LLU};

/**
 * 08
 * CRC-31/PHILIPS
 * width=31 poly=0x04c11db7 init=0x7fffffff refin=false refout=false xorout=0x7fffffff check=0x0ce9e46c name="CRC-31/PHILIPS"
 */
crc_para_t const init009 = {"CRC-31/PHILIPS",0,31,0x04c11db7LLU,0x7fffffffLLU,0x7fffffffLLU,0,0x0ce9e46cLLU};

/**
 * 09
 * CRC-32
 * width=32 poly=0x04c11db7 init=0xffffffff refin=true refout=true xorout=0xffffffff check=0xcbf43926 name="CRC-32"
 */
crc_para_t const init010 = {"CRC-32",0,32,0x04c11db7LLU,0xffffffffLLU,0xffffffffLLU,(CRC_MODE_REV_IN|CRC_MODE_REVOUT),0xcbf43926LLU};

/**
 * 10
 * CRC-32/BZIP2
 * width=32 poly=0x04c11db7 init=0xffffffff refin=false refout=false xorout=0xffffffff check=0xfc891918 name="CRC-32/BZIP2"
 */
crc_para_t const init011 = {"CRC-32",0,32,0x04c11db7LLU,0xffffffffLLU,0xffffffffLLU,0,0xfc891918LLU};

/**
 * 11
 * CRC-32/MPEG-2
 * width=32 poly=0x04c11db7 init=0xffffffff refin=false refout=false xorout=0x00000000 check=0x0376e6e7 name="CRC-32/MPEG-2"
 */
crc_para_t const init012 = {"CRC-32/MPEG-2",0,32,0x04c11db7LLU,0xffffffffLLU,0x00000000LLU,0,0x0376e6e7LLU};

/**
 * 12
 * CRC-40/GSM
 * width=40 poly=0x0004820009 init=0x0000000000 refin=false refout=false xorout=0xffffffffff check=0xd4164fc646 name="CRC-40/GSM"
 */
crc_para_t const init013 = {"CRC-40/GSM",0,40,0x0004820009LLU,0x0000000000LLU,0xffffffffffLLU,0,0xd4164fc646LLU};

/**
 * 13
 * CRC-64
 * width=64 poly=0x42f0e1eba9ea3693 init=0x0000000000000000 refin=false refout=false xorout=0x0000000000000000 check=0x6c40df5f0b497347 name="CRC-64"
 */
crc_para_t const init014 = {"CRC-64",0,64,0x42f0e1eba9ea3693LLU,0x0000000000000000LLU,0x0000000000000000LLU,0,0x6c40df5f0b497347LLU};

/**
 * 14
 * CRC-64/XZ
 * width=64 poly=0x42f0e1eba9ea3693 init=0xffffffffffffffff refin=true refout=true xorout=0xffffffffffffffff check=0x995dc9bbdf1939fa name="CRC-64/XZ"
 */
crc_para_t const init015 = {"CRC-64/XZ",0,64,0x42f0e1eba9ea3693LLU,0xffffffffffffffffLLU,0xffffffffffffffffLLU,(CRC_MODE_REV_IN|CRC_MODE_REVOUT),0x995dc9bbdf1939faLLU};

/**
 * Collection of Public Availible CRC Parameter Sets
 * Allready used / known Good Polynoms and Algo-Variants
 * --> beware of Rigths & Patents before using a Set for
 *     comercial purposes
 * All Sets supplied here are for educational usage only
 * if not stated otherwise
 */
std::array<Algorithms::CRC::crc_para_t,SET_CRC_ELEMENTS> Algorithms::CRC::crc_para_sets = {
          init001,init002,init003,
  init004,init005,init006,init007,
  init008,init009,init010,init011,
  init012,init013,init014,init015
};
