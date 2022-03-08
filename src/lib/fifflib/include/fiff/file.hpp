//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FileEXPLORER_FIFFREADER_HPP
#define FileEXPLORER_FIFFREADER_HPP

#include "tag.hpp"
#include "tagloader.hpp"

#include <io/endian.hpp>
#include <fstream>
#include <string>

namespace Fiff {

class File {
public:
  File() = default;

  explicit File(const std::string &filename);

  void open(const std::string &filename);
  void close();
  bool isOpen() const;

  Tag readNextTag();
  Tag peekNextTag();

  void seek(std::streampos pos);
  std::streampos position();

  bool isAtEnd() const;

private:
  TagLoader mTagLoader;
  std::ifstream mFileIn;
};

}
#endif //FileEXPLORER_FIFFREADER_HPP
