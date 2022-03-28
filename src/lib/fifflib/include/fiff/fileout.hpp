//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_FILEOUT_HPP
#define FIFFFILEEXPLORER_FILEOUT_HPP

#include "fiff/tag.hpp"
#include "core/endian.hpp"

#include <fstream>

namespace Fiff {

class FileOut {
  FileOut() = default;
  explicit FileOut(const std::string &filePath);

  void open(const std::string &filePath);
  bool isOpen()const;

  void writeTag(const Tag &tag);

  void goToWritePosition(std::streampos pos);
  std::streampos currentWritePosition();

protected:
  std::ofstream m_ofstream;
};
}//namespace

#endif //FIFFFILEEXPLORER_FILEOUT_HPP
