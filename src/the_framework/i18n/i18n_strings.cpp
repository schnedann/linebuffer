#include "i18n_strings.h"

/*I18N::i18n_strings::i18n_strings()
{

}*/

std::string I18N::get_i18n_string(I18N::string_ids_t const sel){
  return std::string(strlist[u32(sel)].data,&(strlist[u32(sel)].data)[strlist[u32(sel)].length]);
}
