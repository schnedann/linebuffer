/*
 *  Copyright (c) 2019-2021,Danny Schneider
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

#include <fstream>
#include <sys/stat.h>
#include <cstdio>
#include <cerrno>
#include <cstring>

#include "file_fkt.h"

/**
 * @brief getFileSize
 * @param filename
 * @return
 */

Core::Flow::with_error_t<size_t> File_IO::getFileSize(std::string const& filename){
#ifdef __cpp_lib_filesystem
  std::error_code ec;
  auto res = Core::Flow::make_with_error<size_t>(fs::file_size(filename,ec));
  if(ec){
    res.first = true;
  }
  return res;
#else
  struct stat stat_buf;
  int rc = stat(filename.c_str(), &stat_buf);
  return Core::Flow::make_with_error<size_t>(stat_buf.st_size,(rc!=0));
#endif
}

/**
 * @brief getFileSize
 * @param fd
 * @return
 */
/*std::pair<bool,size_t> File_Fkt::getFileSize(int const fd){
  struct stat stat_buf;
  int rc = fstat(fd, &stat_buf);
  return std::make_pair((rc!=0),stat_buf.st_size);
}*/

/**
 * @brief getBlockSize
 * @param filename
 * @return
 */
Core::Flow::with_error_t<size_t>  File_IO::getBlockSize(std::string const& filename){
  struct stat stat_buf;
  int rc = stat(filename.c_str(), &stat_buf);
  return Core::Flow::make_with_error<size_t>(stat_buf.st_blksize,(rc!=0));
}

/**
 * @brief copy_File
 * @param source - Source File Name
 * @param target - Target File Name
 * @return true on Error
 */
bool File_IO::copy_File(std::string const& source, std::string const& target){
#ifdef __cpp_lib_filesystem
  return !fs::copy_file(source,target);
#else
  bool err = true;
  try{
    std::ifstream  src(source, std::ios::binary | std::ios::in);
    std::ofstream  dst(target, std::ios::binary | std::ios::out);
    if(src){
      if(dst){
        dst << src.rdbuf();
        err = false;
        dst.close();
      }
      src.close();
    }
  }catch(const std::exception& e){
    ERROUT(ERROR(PRNVAR(e.what())))
  }
  return err;
#endif
}

/**
 * @brief rename_File
 * @param source - File 2 Rename
 * @param target - Target File Name
 * @return true on Error
 */
bool File_IO::rename_File(std::string const& source, std::string const& target){
#ifdef __cpp_lib_filesystem
  bool err = true;
  if(fs::exists(source)){
    fs::rename(source,target);
    err = false;
  }
  return err;
#else
  bool err=false;
  if(0>std::rename(source.c_str(), target.c_str())){
    ERROUT(PRNVAR(std::strerror(errno)))
    err = true;
  }
  return err;
#endif
}

#if defined(PREDEF_PLATFORM_UNIX)
/**
 * @brief File_Fkt::chown_File
 * @param filename
 * @param owner
 * @param group
 * @return
 */
bool File_IO::chown_File(std::string const& filename, uid_t owner, gid_t group){
  bool err=false;
  if(0>chown(filename.c_str(), owner, group)){
    ERROUT(PRNVAR(std::strerror(errno)))
    err = true;
  }
  return err;
}

/**
 * @brief File_Fkt::chmod_File
 * @param filename
 * @param mode
 * @param flag
 * @return
 */
bool File_IO::chmod_File(const std::string &filename, mode_t mode){
  bool err=false;
  if(0>chmod(filename.c_str(), mode)){
    ERROUT(PRNVAR(std::strerror(errno)))
    err = true;
  }
  return err;
}

#endif

//----- Read File

/**
 * @brief read_File2String
 * @param filename
 * @return
 */
std::string File_IO::read_File2String(std::string const& filename){
  std::string contents;
  auto fsize = getFileSize(filename);
  //Filesize > 0
  if(!Core::Flow::has_error(fsize) && (0<Core::Flow::get_value(fsize))){
    //Resize String, so it can hold the complete File
    contents.resize(fsize.second);
    try {
      //Open file for read
      std::ifstream file(filename, std::ios::binary | std::ios::in);
      //OK?
      if(file){
        //Read the File
        file.read(&contents[0], long(contents.size()));
        file.close();
      }
    } catch(const std::exception& e){
      ERROUT(PRNVAR(e.what()))
    }
  }
  return(contents);
}

//----- Write Block

bool File_IO::write_block(const std::string &filename, file_data_t const& buffer, size_t const offset)
{
  bool err = true;

  return err;
}

//----- Read Block

/**
 * @brief File_Fkt::read_block
 * @param filename
 * @param offset
 * @param length
 * @return returns a pointer to a self managed, self destructing intermeadiate buffer if first element is false
 *         error if first element is true
 */
[[nodiscard]] Core::Flow::with_error_t<File_IO::file_data_t> File_IO::read_block(std::string const& filename, size_t const offset, size_t const length){

  //auto res = Core::Flow::make_with_error<file_data_t>(std::make_pair(std::unique_ptr<u8[]>(nullptr),size_t(0)));
  auto res = std::make_pair(true,std::make_pair(std::unique_ptr<u8[]>(nullptr),size_t(0)));

  auto fsize = getFileSize(filename);
  if(!Core::Flow::has_error(fsize)){
    //Block is inside file?
    if((offset+length)<=Core::Flow::get_value(fsize)){
      auto ptr = std::unique_ptr<u8[]>(new u8[length]);
      try{
        //Open File
        std::ifstream file(filename, std::ios::binary | std::ios::in);
        //OK?
        if(file){
          //Move Read Position by Offset
          file.seekg(s32(offset),std::ios_base::seekdir::_S_cur);
          //Read Block of data from File
          file.read(reinterpret_cast<char*>(ptr.get()), long(length));
          file.close();

          Core::Flow::set_error(res,false);
          res.second.first  = std::move(ptr);
          res.second.second = length;
        }
      } catch(const std::exception& e){
        ERROUT(PRNVAR(e.what()))
      }
    }
  }
  return res;
}

[[nodiscard]] Core::Flow::with_error_t<File_IO::file_data_t> File_IO::read_block(std::string const& filename, Fields::field_sl<size_t> const& fsl){
  return read_block(filename,Fields::get_start<size_t>(fsl),Fields::get_length<size_t>(fsl));
}

//-----

/*void removeLine(char* sourcefile,int line){
  ifstream infile;
  char tempPath[100]="D:/tempfile.txt";
  infile.open(sourcefile,ios::in);
  if(infile){
    int numLine=countLine(sourcefile);
    if(numLine<line){
       cout<<"\nNo line to delete\n.";
       return;
    }
    ofstream outfile;
    outfile.open(tempPath,ios::out);
    char data[100];
    int i=0;
    while(infile.getline(data,100)){
       i++;
       if(i==line) continue;
       outfile<<data<<"\n";
    }
    outfile.close();
  }
  infile.close();
 remove(sourcefile);
 rename(tempPath,sourcefile);
}

int countLine(char* sourcefile){
  ifstream infile;
  infile.open(sourcefile,ios::in);
  char data[100];
  int line=0;
  while(infile.getline(data,100)) line++;
  return line;
}*/
