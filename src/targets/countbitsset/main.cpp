#include <cstdlib>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <array>
#include <cstdint>
#include <chrono>
#include <type_traits>

#include <functional>

#include "gsl"

#include "dtypes.h"
#include "bitmacros.h"
#include "countbitsset.h"
#include "gccversion.h"
#include "Stringhelper.h"

using namespace std;
using elapsed_resolution = std::chrono::milliseconds;

array<string,9> const algoname = {
  Utility::Strings::make_string_from_literal("Parallel Counting   V1            -> Version of CountBitsSet              "),
  Utility::Strings::make_string_from_literal("Parallel Counting   V2            -> Version of CountBitsSet              "),
  Utility::Strings::make_string_from_literal("Parallel Counting   V3            -> Version of CountBitsSet              "),
  Utility::Strings::make_string_from_literal("Nibble LookUpTable  V1            -> 1 Nibble per cycle only              "),
  Utility::Strings::make_string_from_literal("Nibble LookUpTable  V2            -> 2 Nibbles of a Byte at once          "),
  Utility::Strings::make_string_from_literal("Nibble LUT Unrolled V1            -> Access Bytes by shifts               "),
  Utility::Strings::make_string_from_literal("Nibble LUT Unrolled V2            -> Access Bytes via union (Compiler)    "),
  Utility::Strings::make_string_from_literal("Compiler intrinsic                -> using optimized Assembler if possible"),
  Utility::Strings::make_string_from_literal("wegner methof / briankernighansway-> Human readable Algorithm             ")};

//-----

/**
 * !!! THIS Method calling via std::function<> is slower !!!
 */
using fktptr = u8(*)(u32 const);
static constexpr std::array<fktptr,9> const fut_lst = {
  Algorithms::CountBitsset::parallel<u32>,
  Algorithms::CountBitsset::parallel_2<u32>,
  Algorithms::CountBitsset::parallel_3<u32>,
  Algorithms::CountBitsset::nibble_lut<u32>,
  Algorithms::CountBitsset::nibble_lut2<u32>,
  Algorithms::CountBitsset::nibble_lut_ur<u32>,
  Algorithms::CountBitsset::nibble_lut_ur2<u32>,
  Algorithms::CountBitsset::intrinsic_popcnt<u32>,
  Algorithms::CountBitsset::wegner_method<u32>
};

//-----

int main(int argc __attribute__((unused)), char **argv __attribute__((unused))){

  cout << "Compiler Version: " << dGNUC_VERSION << "\n";
  cout << "Build Date      : " << __DATE__ << "\n";

  volatile u32 res = 0;
  cout << "Benchmarking Algorithms for \"Count Set Bits\"" << "\n";
  cout << "Running all Algorithms with Input from 0 to 4294967295..." << "\n";
  for(u8 ii=0; ii<u8(fut_lst.size()); ++ii){

    cout << "Algorithm " << u16(ii) << ": " << gsl::at(algoname,ii) << " "; // << "\n";
    std::chrono::high_resolution_clock::time_point start_time = std::chrono::high_resolution_clock::now();
    for(u32 ij=0; ij<Math::Boolean::GETFULLMASK<u32>(); ++ij){
      res = gsl::at(fut_lst,ii)(ij);
    }
    std::chrono::high_resolution_clock::time_point stop_time = std::chrono::high_resolution_clock::now();
    elapsed_resolution dtime =std::chrono::duration_cast<elapsed_resolution>(stop_time - start_time);

    cout << static_cast<float>(dtime.count())/1000.0f << "[s]" << "\n";
  }
  if(res == 0){
    cout << "Zero" << "\n";
  }
  return 0;
}
