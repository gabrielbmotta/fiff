//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFF_LIBFIFF_OUTPUT_HPP
#define FIFF_LIBFIFF_OUTPUT_HPP

#include "tag.hpp"
#include <core/endian.hpp>

#include <fstream>
#include <memory>

namespace Fiff {

class Output {
public:
  Output();

  ~Output();

  void writeTag(const Tag &tag);

  void goToWritePosition(std::streampos pos);
  std::streampos currentWritePosition();

  static Output toFile(const std::string &filePath);
  static Output toFile(const std::string &filePath, Endian::Absolute fileEndian);

  void setEndianess(Endian::Absolute endianness);
  Endian::Absolute getEndianess() const;
protected:

  Endian::Relative m_relativeEndian;
  std::ostream* m_ostream;
};
}//namespace

#endif //FIFF_LIBFIFF_OUTPUT_HPP
