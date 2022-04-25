/**
 *  @file   filein.hpp
 **/

#ifndef FIFFFILEEXPLORER_INPUT_HPP
#define FIFFFILEEXPLORER_INPUT_HPP

#include "tag.hpp"
#include "../core/endian.hpp"

#include <fstream>
#include <memory>

namespace Fiff{

/**
 * Class to read in a fiff file tag by tag.
 */
class Input{
public:
  Input();

  Tag getTag();
  Tag peekTag();

  void goToReadPosition(std::streampos pos);
  std::streampos currentReadPosition() const;
  bool atEnd() const;

  static Input fromFile(const std::string &filePath);
  static Input fromFile(const std::string &filePath, Endian fileEndian);

  Endian getEndianess() const;
  void setEndianess(Endian fileEndian);
protected:
  void setEndianess();

  void readMetaData(Tag& tag);
  void readData(Tag& tag);

  RelativeEndian m_relativeEndian;
  std::unique_ptr<std::istream> m_istream;
};

} //namespace
#endif //FIFFFILEEXPLORER_INPUT_HPP
