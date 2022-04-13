//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_OUTPUT_HPP
#define FIFFFILEEXPLORER_OUTPUT_HPP

#include "fiff/tag.hpp"
#include "core/endian.hpp"

#include <fstream>
#include <memory>

namespace Fiff {

class Output {
public:
  Output() = default;

  void writeTag(Tag &tag);

  void goToWritePosition(std::streampos pos);
  std::streampos currentWritePosition();

  static Output toFile(const std::string &filePath);

  RelativeEndian m_relativeEndian;
protected:
  std::unique_ptr<std::ostream> m_ostream;
};
}//namespace

#endif //FIFFFILEEXPLORER_OUTPUT_HPP
