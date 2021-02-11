#ifndef LINEBUFFER_H
#define LINEBUFFER_H

#include <string>

#include "dtypes.h"
#include "dbllnkdlst.h"

class linebuffer
{
private:
  Datastructures::dbllnkdlst<std::string> dll;

  std::string prefix;
  std::string postfix;
  std::string delimiter;
public:
   linebuffer()=default;
  ~linebuffer()=default;

  void add(std::string const& str);
  with_error_t<std::string> get_all_lines();
  size_t size();
};

#endif // LINEBUFFER_H
