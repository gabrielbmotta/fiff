//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_FILEIN_HPP
#define FIFFFILEEXPLORER_FILEIN_HPP

#include "fiff/tag.hpp"
#include "core/endian.hpp"

#include <fstream>

namespace Fiff{

class FileIn{
public:
  FileIn();
  explicit FileIn(const std::string &filePath);
  FileIn(const std::string &filePath, Endian fileEndian);

  void open(const std::string &filePath);
  void open(const std::string &filePath, Endian fileEndian);
  bool isOpen()const;

  Tag readNextTag();
  Tag peekNextTag();

  void goToReadPosition(std::streampos pos);
  std::streampos currentReadPosition();
  bool atEnd();

private:
  void setEndianess();
  void setEndianess(Endian fileEndian);

  void readMetaData(Tag& tag);
  void readData(Tag& tag);

  std::ifstream m_ifstream;
  RelativeEndian m_relativeEndian;
};

} //namespace
#endif //FIFFFILEEXPLORER_FILEIN_HPP
