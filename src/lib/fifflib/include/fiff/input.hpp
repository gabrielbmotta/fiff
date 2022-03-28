/**
 *  @file   filein.hpp
 **/

#ifndef FIFFFILEEXPLORER_INPUT_HPP
#define FIFFFILEEXPLORER_INPUT_HPP

#include "fiff/tag.hpp"
#include "core/endian.hpp"

#include <fstream>
#include <memory>

namespace Fiff{

/**
 * Class to read in a fiff file tag by tag.
 */
class Input{
public:
  Input();

  Tag readNextTag();
  Tag peekNextTag();

  void goToReadPosition(std::streampos pos);
  std::streampos currentReadPosition();
  bool atEnd();

  static Input fromFile(const std::string &filePath);
  static Input fromFile(const std::string &filePath, Endian fileEndian);

private:
  void setEndianess();
  void setEndianess(Endian fileEndian);

  void readMetaData(Tag& tag);
  void readData(Tag& tag);

  std::unique_ptr<std::istream> m_istream;
  RelativeEndian m_relativeEndian;
};

} //namespace
#endif //FIFFFILEEXPLORER_INPUT_HPP
