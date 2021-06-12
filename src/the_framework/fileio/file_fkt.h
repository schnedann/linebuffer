/*
 *  Copyright (c) 2019,Danny Schneider
 *  All rights reserved.
 *
 *  Redistribution and use in source and binary forms, with or without
 *  modification, are permitted provided that the following conditions are met:
 *
 *  * Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 *  * Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 *  DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 *  FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 *  DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 *  SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 *  CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 *  OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef FILE_FKT_H
#define FILE_FKT_H

#include <iostream>
#include <string>
#include <array>
#include <fstream>
#include <memory>
#include <utility>

#include <version>
#ifdef __cpp_lib_filesystem
  #include <filesystem>
  namespace fs = std::filesystem;
#endif

#include "dtypes.h"
#include "env_detect.h"
#include "error_mgnt.h"
#include "fields.h"
#include "debug_hlp.h"

namespace File_IO {

//----- get Metadata

[[nodiscard]] Core::Flow::with_error_t<size_t> getFileSize(std::string const& filename);
[[nodiscard]] Core::Flow::with_error_t<size_t> getBlockSize(std::string const& filename);
//template<size_t CNT> bool read_from_File(std::string  const& filename, std::array<u8,CNT>& buffer);

//----- Read

std::string read_File2String(std::string const& filename);

/**
 * @brief read_from_File - Open File and fill supplied buffer
 * @return true on error e.g. file does not exist, failed to open, or is smaller than the buffer
 */

//std::unique_ptr<u8[]>
template<size_t CNT> [[nodiscard]] bool read_from_File(std::string  const& filename, std::array<u8,CNT>& buffer){
  bool err = true;
  auto fsize = getFileSize(filename);
  if(!fsize.first){
    if(fsize.second>=buffer.size()){
      try {
        std::ifstream file(filename, std::ios::binary | std::ios::in);
        if(file){
          file.read(reinterpret_cast<char*>(buffer.data()),long(buffer.size()));
          file.close();
          err = false;
        }
      } catch(const std::exception& e){
        ERROUT(PRNVAR(e.what()))
      }
    }
  }
  return err;
}

//----- Read n Write Block

using file_data_t = std::pair<std::unique_ptr<u8[]>,size_t>;
[[nodiscard]] bool write_block(std::string const& filename, file_data_t const& buffer, size_t const offset);
[[nodiscard]] Core::Flow::with_error_t<file_data_t> read_block(std::string const& filename, size_t const offset, size_t const length);
[[nodiscard]] Core::Flow::with_error_t<file_data_t> read_block(std::string const& filename, Fields::field_sl<size_t> const& fsl);

//-----

[[nodiscard]] bool copy_File(  std::string const& source, std::string const& target);
[[nodiscard]] bool rename_File(std::string const& source, std::string const& target);

#if defined(PREDEF_PLATFORM_UNIX)
[[nodiscard]] bool chown_File(std::string const& filename, uid_t owner, gid_t group);
[[nodiscard]] bool chmod_File(std::string const& filename, mode_t mode);
#endif

//-----

}

#endif // FILE_FKT_H
