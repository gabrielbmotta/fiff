//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_FILEOUT_HPP
#define FIFFFILEEXPLORER_FILEOUT_HPP

#include "fiff/tag.hpp"

#include <fstream>

class FileOut{
//  FileOut() = default;
//  FileOut(const std::string& filePath);
//
//  void open(const std::string &filePath);
//  void open();
//  bool isOpen();
//
//  void writeTag(const Tag& tag);
//
//  void goToWritePosition(std::streampos pos);
//  std::streampos currentWritePosition();

protected:
  std::ofstream m_ofstream;
};


#endif //FIFFFILEEXPLORER_FILEOUT_HPP
