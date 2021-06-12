
#include "dtypes.h"
#include "debug_hlp.h"
#include "env_detect.h"
#include "Stringhelper.h"

using namespace std;

int main(){
  DBGOUT("Hello World!")
  DBGOUT(PRNVAR(Enviroment::Endianness::is_expected(Enviroment::Endianness::endianness_t::ENDIAN_LITTLE)));
  return 0;
}
