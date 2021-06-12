#include <iostream>
#include <array>

#include "dtypes.h"
#include "file_fkt.h"
#include "debug_hlp.h"
#include "iterators.h"

using namespace std;

int main(){

  {
    static constexpr size_t const buffersize = 12;
    array<u8,buffersize> buff{};

    DBGOUT(File_IO::read_from_File<buffersize>("dummy.txt",buff))
    DBGOUT(std::string(buff.begin(),buff.end()))

    //---

    auto content = File_IO::read_File2String("dummy.txt");
    DBGOUT(PRNVAR(content))
    DBGOUT(PRNVAR(content.size()))

    //---

    auto fsize = File_IO::getFileSize("dummy.txt");
    if(!Core::Flow::has_error(fsize)){
      DBGOUT(PRNVAR(Core::Flow::get_value(fsize)))
    }

    //---

    auto bsize = File_IO::getBlockSize("dummy.txt");
    if(!Core::Flow::has_error(bsize)){
      DBGOUT(PRNVAR(Core::Flow::get_value(bsize)))
    }
  }

  //---

  {
    static_cast<void>(File_IO::copy_File("dummy.txt","dummy.txt~"));
    static_cast<void>(File_IO::rename_File("dummy.txt~","dummy.bak"));
  }

  //---

  {
    auto rd_data = File_IO::read_block("dummy.bak",Fields::make_field_sl<size_t>(0,5));
    if(!Core::Flow::has_error(rd_data)){
      auto bgn = reinterpret_cast<Core::Container::iterator_t<char>>(Core::Flow::get_value(rd_data).first.get());
      /*char* end = &reinterpret_cast<char*>(rd_data.second.first.get())[rd_data.second.second];
      DBGOUT(std::string(bgn,end))*/
      DBGOUT(std::string(bgn,rd_data.second.second))
    }
  }

  //---

  {
    auto rd_data = File_IO::read_block("dummy.bak", Fields::make_field_sl<size_t>(6,5));
    if(!Core::Flow::has_error(rd_data)){
      auto bgn = reinterpret_cast<Core::Container::iterator_t<char>>(Core::Flow::get_value(rd_data).first.get());
      /*char* end = &reinterpret_cast<char*>(rd_data.second.first.get())[rd_data.second.second];
      DBGOUT(std::string(bgn,end))*/
      DBGOUT(std::string(bgn,rd_data.second.second))
    }
  }

  return 0;
}
