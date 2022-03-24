//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_FILEOUT_HPP
#define FIFFFILEEXPLORER_FILEOUT_HPP

#include "fiff/tagoutstream.hpp"
#include <fstream>

class FileOut : TagOutStream{
  FileOut() = default;
  FileOut(const std::string& filePath);

  void open(const std::string &filePath);
  void open();
  bool isOpen();
};


#endif //FIFFFILEEXPLORER_FILEOUT_HPP
