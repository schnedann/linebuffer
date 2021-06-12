#ifndef I18N_STRINGS_H
#define I18N_STRINGS_H

#include <array>
#include <string>

#include "dtypes.h"

namespace I18N {

enum class string_ids:u32{
  s00001 = 0,
  s00002 = 1,
  end_of_enum = 2
};
using string_ids_t = string_ids;

struct i18n_string{
  u8 const* data;
  u32 dummy;
  u32 length;
};

constexpr u8 const str00001[] = "Test1";
constexpr u8 const str00002[] = "Test2";

constexpr static std::array<i18n_string,2> const strlist ={
  {{str00001,0,(sizeof(str00001)-1)},
   {str00002,0,(sizeof(str00002)-1)}}
};

std::string get_i18n_string(string_ids_t const sel);

/*
class i18n_strings
{
public:
    i18n_strings();
};
*/
}

#endif // I18N_STRINGS_H
