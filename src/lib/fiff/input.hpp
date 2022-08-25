/**
 *  @file   filein.hpp
 **/

#ifndef FIFF_LIBFIFF_INPUT_HPP
#define FIFF_LIBFIFF_INPUT_HPP

#include "tag.hpp"
#include <core/endian.hpp>

#include <fstream>
#include <memory>

namespace Fiff{

/**
 * Class to read in a fiff file tag by tag.
 */
class Input{
public:
  Input();
  ~Input();

  Tag getTag();
  Tag peekTag();

  void goToReadPosition(std::streampos pos);
  std::streampos currentReadPosition() const;
  bool atEnd() const;

  static Input fromFile(const std::string &filePath);
  static Input fromFile(const std::string &filePath, Endian::Absolute fileEndian);

  Endian::Absolute getEndianess() const;
  void setEndianess(Endian::Absolute fileEndian);
protected:
  void setEndianess();

  void readMetaData(Tag& tag);
  void readData(Tag& tag);

  Endian::Relative m_relativeEndian;
  std::istream* m_istream;
};

} //namespace
#endif //FIFF_LIBFIFF_INPUT_HPP
