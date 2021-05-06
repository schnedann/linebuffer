#include <cstring>
#include <array>

#include "ntp_client.h"
#include "ovf_save.h"
#include "moving_average.h"
#include "median_filter.h"

#include <sys/time.h>

using namespace std;

uint32_t ntp_timestamp_format_u32(ntp_short_format& ntptsf){
  return *(reinterpret_cast<uint32_t*>(&ntptsf));
}

uint64_t ntp_timestamp_format_u64(ntp_timestamp_format& ntptsf){
  return *(reinterpret_cast<uint64_t*>(&ntptsf));
}

//-----

ntp_client::ntp_client():packet(reinterpret_cast<ntp_packet_v4_t*>(buffer.data()))
{

}

/**
 * @brief ntp_client::LI
 * @param packet
 * @return
 */
uint8_t ntp_client::LI(ntp_packet_v3_t const& packet){
  return ((packet.li_vn_mode & 0xC0u) >> LI_offset); //  (li   & 11 000 000) >> 6
}

/**
 * @brief ntp_client::VN
 * @param packet
 * @return
 */
uint8_t ntp_client::VN(ntp_packet_v3_t const& packet){
  return ((packet.li_vn_mode & 0x38) >> VER_offset); //  (vn   & 00 111 000) >> 3
}

/**
 * @brief ntp_client::MODE
 * @param packet
 * @return
 */
uint8_t ntp_client::MODE(ntp_packet_v3_t const& packet){
  return ((packet.li_vn_mode & 0x07) >> Mode_offset); // (mode & 00 000 111) >> 0
}

/**
 * @brief ntp_client::prepare_to_send
 * @return
 */
char *ntp_client::prepare_to_send(){
  memset(buffer.data(),0,buffer.size());
  buffer[0] = 0x1Bu;
  return reinterpret_cast<char*>(buffer.data());
}

/**
 * @brief ntp_client::receive_buffer
 * @return
 */
char *ntp_client::receive_buffer(){
  return reinterpret_cast<char*>(buffer.data());
}

/**
 * @brief ntp_client::data
 * @return
 */
ntp_packet_v3_t *ntp_client::data()
{
  return reinterpret_cast<ntp_packet_v3_t*>(buffer.data());
}

/**
 * @brief roundtrip_delay
      Let t1, t2 and t3
      represent the contents of the Originate Timestamp, Receive
      Timestamp and Transmit Timestamp fields and t4 the local time the
      NTP message is received.  Then the roundtrip delay d is:

         d = (t4 - t1) - (t3 - t2)
 * @param tstamps
 * @return
 */
uint64_t ntp_client::roundtrip_delay(array<ntp_timestamp_format_t,4> tstamps){
  static moving_average<uint64_t,11> ma;//~3min
  static median_filter<uint64_t,5>   mf;

  Math::OverflowSafe::ovf_save ofs;
  // local time - Originate Timestamp (Total Handshake time)
  uint64_t x = ofs.sub<uint64_t>(ntp_timestamp_format_u64(tstamps[3]),ntp_timestamp_format_u64(tstamps[0]));
  if(ofs.get_of()){
    x = (~x)+1;
  }
  // Transmit Timestamp - Receive Timestamp (Server Processing Time)
  uint64_t y = ofs.sub<uint64_t>(ntp_timestamp_format_u64(tstamps[2]),ntp_timestamp_format_u64(tstamps[1]));
  if(ofs.get_of()){
    y = (~y)+1;
  }
  // Total Handshake time - Server Processing Time = Packet Travel Time
  uint64_t z = ofs.sub<uint64_t>(x,y);
  if(ofs.get_of()){
    z = (~z)+1;
  }

  mf.filter(z);        //Filter Outliers
  ma.simple(mf.get()); //Average Messurements
  return ma.get_s();
};

/**
 * @brief clock_offset
      Let t1, t2 and t3
      represent the contents of the Originate Timestamp, Receive
      Timestamp and Transmit Timestamp fields and t4 the local time the
      NTP message is received.  Then the clock offset c is:

         c = (t2 - t1 + t3 - t4)/2 .
 * @param tstamps
 * @return
 */
uint64_t ntp_client::clock_offset(array<ntp_timestamp_format_t,4> tstamps){
  static moving_average<uint64_t,11> ma;//~3min
  static median_filter<uint64_t,5>   mf;

  Math::OverflowSafe::ovf_save ofs;
  // Receive Timestamp - Originate Timestamp
  uint64_t x = ofs.sub<uint64_t>(ntp_timestamp_format_u64(tstamps[1]),ntp_timestamp_format_u64(tstamps[0]));
  if(ofs.get_of()){
    x = (~x)+1;
  }
  // Transmit Timestamp - local time
  uint64_t y = ofs.sub<uint64_t>(ntp_timestamp_format_u64(tstamps[2]),ntp_timestamp_format_u64(tstamps[3]));
  if(ofs.get_of()){
    y = (~y)+1;
  }
  //
  uint64_t z = ofs.add<uint64_t>(x,y);
  if(ofs.get_of()){
    z = (~z)+1;
  }

  mf.filter(z>>1);     //Filter Outliers
  ma.simple(mf.get()); //Average Messurements
  return ma.get_s();
};

/**
 * @brief ntp_client::to_ns_tstamp
 * @param ptr
 * @return
 */
uint64_t ntp_client::to_ns_tstamp(uint32_t* ptr __attribute__((unused))){

  return 0;
}

/**
 * @brief ntp_client::test_for_kod - Test for Kiss of Death from Server
 * @param ptr
 * @return - do we need to die anyway?
 */
Kod_Result ntp_client::test_for_kod(ntp_packet_v3_t* ptr)
{
  Kod_Result res = Kod_Result::ignored;

  if(0==(ptr->stratum)){
    uint8_t* msgptr = reinterpret_cast<uint8_t*>(&(ptr->refId));
    if('X' == static_cast<char>(msgptr[0])){
      res = Kod_Result::XCode;
    }else{
      { //Deny
        uint8_t const patoffset = 4*5;
        bool equal = true;
        for(u_int8_t ii=0; (equal && (ii<4)); ++ii){
          if(Kiss_Codes[ii+patoffset]!=msgptr[ii]){
            equal = false;
          }
        }
        if(equal) res = Kod_Result::DENY;
      }
      if(res == Kod_Result::ignored){ //Rstr
        uint8_t const patoffset = 4*7;
        bool equal = true;
        for(u_int8_t ii=0; (equal && (ii<4)); ++ii){
          if(Kiss_Codes[ii+patoffset]!=msgptr[ii]){
            equal = false;
          }
        }
        if(equal) res = Kod_Result::RSTR;
      }
      if(res == Kod_Result::ignored){ //Rate
        uint8_t const patoffset = 4*11;
        bool equal = true;
        for(u_int8_t ii=0; (equal && (ii<4)); ++ii){
          if(Kiss_Codes[ii+patoffset]!=msgptr[ii]){
            equal = false;
          }
        }
        if(equal) res = Kod_Result::RATE;
      }
    }
  }
  return res;
}

/**
 * @brief ntp_client::wait
 */
void ntp_client::wait()
{
  timespec sleeptime{};
  timespec remaintime{};

  clock_gettime(CLOCK_MONOTONIC, &sleeptime);

  constexpr static uint32_t const wait__s  =         16;
  //                                         smmmuuunnnppp
  constexpr static uint32_t const wait_ns  =  000000000;
  constexpr static uint32_t const ns_per_s = 1000000000;

  sleeptime.tv_nsec += wait_ns;
  sleeptime.tv_sec  += (wait__s + ((sleeptime.tv_nsec>ns_per_s)?(1):(0)));
  sleeptime.tv_nsec %= ns_per_s;

  clock_nanosleep(CLOCK_MONOTONIC,TIMER_ABSTIME,&sleeptime,&remaintime);
  return;
}
