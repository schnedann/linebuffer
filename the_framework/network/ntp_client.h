#ifndef NTP_CLIENT_H
#define NTP_CLIENT_H

#include <cstdint>
#include <cstddef>
#include <string>
#include <array>

/**************************************************
 *
 **************************************************/



/**************************************************
 * Global Parameters from Spec
 **************************************************/

constexpr static uint16_t const NTP_DEFAULT_PORT      = 123      ; // NTP port number
constexpr static uint8_t  const NTP_DEFAULT_VERSION   = 3        ; // NTP version number
constexpr static uint64_t const NTP_DEFAULT_TOLERANCE = 64425    ; // 15e-6 frequency tolerance PHI (s/s)
constexpr static uint16_t const NTP_DEFAULT_MINPOLL   = 4        ; // minimum poll exponent (16 s)
constexpr static uint16_t const NTP_DEFAULT_MAXPOLL   = 17       ; // maximum poll exponent (36 h)
constexpr static uint16_t const NTP_DEFAULT_MAXDISP   = 16       ; // maximum dispersion (16 s)
constexpr static uint64_t const NTP_DEFAULT_MINDISP   = 21474837 ; // .005 minimum dispersion increment (s)
constexpr static uint16_t const NTP_DEFAULT_MAXDIST   = 1        ; // distance threshold (1 s)
constexpr static uint16_t const NTP_DEFAULT_MAXSTRAT  = 16       ; // maximum stratum number

/**************************************************
 * NTP Time & Data Types
 **************************************************/

struct __attribute__((packed)) ntp_short_format {
  uint16_t seconds;
  uint16_t fraction;
};
using ntp_short_format_t = ntp_short_format;
uint32_t ntp_timestamp_format_u32(ntp_short_format& ntptsf);

struct __attribute__((packed)) ntp_timestamp_format{
  uint32_t seconds;
  uint32_t fraction;
};
using ntp_timestamp_format_t = ntp_timestamp_format;
uint64_t ntp_timestamp_format_u64(ntp_timestamp_format& ntptsf);

struct __attribute__((packed)) ntp_date_format{
  uint32_t era_number;
  uint32_t era_offset;
  uint32_t fraction;
};
using ntp_date_format_t = ntp_date_format;

/**************************************************
 * ...some Enums
 **************************************************/

enum class Leap_Indicator:uint8_t{
  no_warning    = 0,
  positive_leap = 1, //last minute of the day has 61 seconds
  negative_leap = 2, //last minute of the day has 59 seconds
  unknown       = 3  //clock unsynchronized
};

enum class Association_Modes:uint8_t{
  reserved            = 0 ,
  symmetric_active    = 1 ,
  symmetric_passive   = 2 ,
  client              = 3 ,
  server              = 4 ,
  broadcast           = 5 ,
  NTP_control_message = 6 ,
  reserved_fpu        = 7 //for private use
};

enum class Packet_Stratum:uint8_t{
  unspecified      = 0  , //or invalid
  primary_server   = 1  , //e.g., equipped with a GPS receiver
  secondary_server = 2  , //via NTP
  unsynchronized   = 16 ,
  reserved_17_255  = 255
};

constexpr static uint8_t const LI_offset   = 6;
constexpr static uint8_t const VER_offset  = 3;
constexpr static uint8_t const Mode_offset = 0;

/**************************************************
 * Kiss of Death
 **************************************************/

/**
 * @brief The Kod_Result enum
 */
enum class Kod_Result:uint8_t{
  noKod   = 0,
  DENY    = 1,
  RSTR    = 2,
  RATE    = 3,
  XCode   = 4,
  ignored = 5
};

constexpr static uint8_t const num_kiss_codes = 14;

/**
 * @brief List of 4Byte ASCII encoded Kiss Codes
 */
static std::array<uint8_t,(4*num_kiss_codes)> const Kiss_Codes = {
  0x41u,0x43u,0x53u,0x54, //ACST    1
  0x41u,0x55u,0x54u,0x48, //AUTH    2
  0x41u,0x55u,0x54u,0x4F, //AUTO    3
  0x42u,0x43u,0x53u,0x54, //BCST    4
  0x43u,0x52u,0x59u,0x50, //CRYP    5
  0x44u,0x45u,0x4Eu,0x59, //DENY*   6
  0x44u,0x52u,0x4Fu,0x50, //DROP    7
  0x52u,0x53u,0x54u,0x52, //RSTR*   8
  0x49u,0x4Eu,0x49u,0x54, //INIT    9
  0x4Du,0x43u,0x53u,0x54, //MCST   10
  0x4Eu,0x4Bu,0x45u,0x59, //NKEY   11
  0x52u,0x41u,0x54u,0x45, //RATE*  12
  0x52u,0x4Du,0x4Fu,0x54, //RMOT   13
  0x53u,0x54u,0x45u,0x50  //STEP   14
};

static std::array<std::string,num_kiss_codes> const Kiss_Strings = {
  "The association belongs to a unicast server Server                                                    ",
  "authentication failed                                                                                 ",
  "Autokey sequence failed                                                                               ",
  "The association belongs to a broadcast server                                                         ",
  "Cryptographic authentication or identification failed                                                 ",
  "Access denied by remote server                                                                        ",
  "Lost peer in symmetric mode                                                                           ",
  "Access denied due to local policy                                                                     ",
  "The association has not yet synchronized for the first time                                           ",
  "The association belongs to a dynamically discovered server                                            ",
  "No key found. Either the key was never installed or is not trusted                                    ",
  "Rate exceeded. The server has temporarily denied access because the client exceeded the rate threshold",
  "Alteration of association from a remote host running ntpdc.                                           ",
  "A step change in system time has occurred, but the association has not yet resynchronized             "
};

/**************************************************
 * V3 Packet as Structure
 **************************************************/

// Structure that defines the 48 byte NTP packet protocol.
struct __attribute__((packed)) ntp_packet_v3{
  uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
                           // li.   Two bits.   Leap indicator.
                           // vn.   Three bits. Version number of the protocol.
                           // mode. Three bits. Client will pick mode 3 for client.

  uint8_t stratum;         // Eight bits. Stratum level of the local clock.
  uint8_t poll;            // Eight bits. Maximum interval between successive messages.
  uint8_t precision;       // Eight bits. Precision of the local clock.

  uint32_t rootDelay;      // 32 bits. Total round trip delay time.
  uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
  uint32_t refId;          // 32 bits. Reference clock identifier.

  /*
   NTP timestamps are represented as a 64-bit fixed-point number, in
   seconds relative to 0000 UT on 1 January 1900.  The integer part is
   in the first 32 bits and the fraction part in the last 32 bits, as
   shown in the following diagram.

       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Integer Part                          |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Fraction Part                         |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   This format allows convenient multiple-precision arithmetic and
   conversion to Time Protocol representation (seconds), but does
   complicate the conversion to ICMP Timestamp message representation
   (milliseconds).  The low-order fraction bit increments at about
   ~0.233 nanosecond intervals, so a free-running one-millisecond clock
   will be in error only a small fraction of one part per million, or
   less than a second per year.
   [Fractional Part Precision: ~232,83064365387 ps]

   Reference Timestamp
      This is a 64-bit timestamp established by the server or client
      host as the timestamp (presumably obtained from a reference clock)
      most recently used to update the local clock.  If the local clock
      has never been synchronized, the value is zero.

   Originate Timestamp
      This is a 64-bit timestamp established by the client host and
      specifying the local time at which the request departed for the
      service host.  It will always have a nonzero value.

   Receive Timestamp
      This is a 64-bit timestamp established by the server host and
      specifying the local time at which the request arrived from the
      client host.  If no request has ever arrived from the client the
      value is zero.

   Transmit Timestamp
      This is a 64-bit timestamp established by the server host and
      specifying the local time at which the reply departed for the
      client host.  If no request has ever arrived from the client the
      value is zero.
  */

/*
  Reference Timestamp: Time when the system clock was last set or corrected, in NTP timestamp format.

  Origin Timestamp (org): Time at the client when the request departed for the server, in NTP timestamp format.

  Receive Timestamp (rec): Time at the server when the request arrived from the client, in NTP timestamp format.

  Transmit Timestamp (xmt): Time at the server when the response left for the client, in NTP timestamp format.

  Destination Timestamp (dst): Time at the client when the reply arrived from the server, in NTP timestamp format.
  Note: Destination Timestamp field is not included as a header field; it is determined upon arrival of the packet
  and made available in the packet buffer data structure.
*/

  uint32_t refTm_s;   // 32 bits. Reference time-stamp seconds.
  uint32_t refTm_f;   // 32 bits. Reference time-stamp fraction of a second.

  uint32_t origTm_s;  // 32 bits. Originate time-stamp seconds.
  uint32_t origTm_f;  // 32 bits. Originate time-stamp fraction of a second.

  uint32_t rxTm_s;    // 32 bits. Received time-stamp seconds.
  uint32_t rxTm_f;    // 32 bits. Received time-stamp fraction of a second.

  uint32_t txTm_s;    // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
  uint32_t txTm_f;    // 32 bits. Transmit time-stamp fraction of a second.
};
using ntp_packet_v3_t = ntp_packet_v3;

/**************************************************
 * V4 Packet as Structure
 **************************************************/

// Structure that defines the 48 byte NTP packet protocol.
struct __attribute__((packed)) ntp_packet_v4{
  uint8_t li_vn_mode;      // Eight bits. li, vn, and mode.
                           // li.   Two bits.   Leap indicator.
                           // vn.   Three bits. Version number of the protocol.
                           // mode. Three bits. Client will pick mode 3 for client.

  uint8_t stratum;         // Eight bits. Stratum level of the local clock.
  uint8_t poll;            // Eight bits. Maximum interval between successive messages.
  uint8_t precision;       // Eight bits. Precision of the local clock.

  uint32_t rootDelay;      // 32 bits. Total round trip delay time.
  uint32_t rootDispersion; // 32 bits. Max error aloud from primary clock source.
  uint32_t refId;          // 32 bits. Reference clock identifier.

  /*
   NTP timestamps are represented as a 64-bit fixed-point number, in
   seconds relative to 0000 UT on 1 January 1900.  The integer part is
   in the first 32 bits and the fraction part in the last 32 bits, as
   shown in the following diagram.

       0                   1                   2                   3
       0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Integer Part                          |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+
      |                         Fraction Part                         |
      +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+

   This format allows convenient multiple-precision arithmetic and
   conversion to Time Protocol representation (seconds), but does
   complicate the conversion to ICMP Timestamp message representation
   (milliseconds).  The low-order fraction bit increments at about
   ~0.233 nanosecond intervals, so a free-running one-millisecond clock
   will be in error only a small fraction of one part per million, or
   less than a second per year.
   [Fractional Part Precision: ~232,83064365387 ps]

   Reference Timestamp
      This is a 64-bit timestamp established by the server or client
      host as the timestamp (presumably obtained from a reference clock)
      most recently used to update the local clock.  If the local clock
      has never been synchronized, the value is zero.

   Originate Timestamp
      This is a 64-bit timestamp established by the client host and
      specifying the local time at which the request departed for the
      service host.  It will always have a nonzero value.

   Receive Timestamp
      This is a 64-bit timestamp established by the server host and
      specifying the local time at which the request arrived from the
      client host.  If no request has ever arrived from the client the
      value is zero.

   Transmit Timestamp
      This is a 64-bit timestamp established by the server host and
      specifying the local time at which the reply departed for the
      client host.  If no request has ever arrived from the client the
      value is zero.
  */

/*
  Reference Timestamp: Time when the system clock was last set or corrected, in NTP timestamp format.

  Origin Timestamp (org): Time at the client when the request departed for the server, in NTP timestamp format.

  Receive Timestamp (rec): Time at the server when the request arrived from the client, in NTP timestamp format.

  Transmit Timestamp (xmt): Time at the server when the response left for the client, in NTP timestamp format.

  Destination Timestamp (dst): Time at the client when the reply arrived from the server, in NTP timestamp format.
  Note: Destination Timestamp field is not included as a header field; it is determined upon arrival of the packet
  and made available in the packet buffer data structure.
*/

  uint32_t refTm_s;   // 32 bits. Reference time-stamp seconds.
  uint32_t refTm_f;   // 32 bits. Reference time-stamp fraction of a second.

  uint32_t origTm_s;  // 32 bits. Originate time-stamp seconds.
  uint32_t origTm_f;  // 32 bits. Originate time-stamp fraction of a second.

  uint32_t rxTm_s;    // 32 bits. Received time-stamp seconds.
  uint32_t rxTm_f;    // 32 bits. Received time-stamp fraction of a second.

  uint32_t txTm_s;    // 32 bits and the most important field the client cares about. Transmit time-stamp seconds.
  uint32_t txTm_f;    // 32 bits. Transmit time-stamp fraction of a second.

  uint32_t extfield1; // Extension Field 1
  uint32_t extfield2; // Extension Field 2
  uint32_t keyid;     // Key Identifier
  uint32_t dgst;      // Digest
};
using ntp_packet_v4_t = ntp_packet_v4;

/**************************************************
 * NTP Client Implementation
 **************************************************/

class ntp_client
{
private:
  std::array<uint8_t,48> buffer{};
  ntp_packet_v4_t* packet;
public:
  ntp_client();

  constexpr static uint32_t const NTP_TIMESTAMP_DELTA = 2208988800ull;
  constexpr static size_t const packetsize = 48;

  static uint8_t LI(ntp_packet_v3_t const& packet);
  static uint8_t VN(ntp_packet_v3_t const& packet);
  static uint8_t MODE(ntp_packet_v3_t const& packet);

  char *prepare_to_send();
  char *receive_buffer();

  ntp_packet_v3_t* data();

  uint64_t roundtrip_delay(std::array<ntp_timestamp_format_t,4> tstamps);
  uint64_t clock_offset(std::array<ntp_timestamp_format_t,4> tstamps);
  uint64_t to_ns_tstamp(uint32_t* ptr);

  Kod_Result test_for_kod(ntp_packet_v3_t* ptr);

  void wait();
};

#endif // NTP_CLIENT_H
