//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FileEXPLORER_FIFFREADER_HPP
#define FileEXPLORER_FIFFREADER_HPP

#include "tag.hpp"

#include <io/endian.hpp>
#include <fstream>
#include <string>

namespace Fiff {

class File {
public:
  File() : mFileIn(), mFileEndianess(RelativeEndian::undetermined)
  {};

  explicit File(const std::string &filename);

  explicit File(const std::string &filename, bool sameEndianAsSystem);

  void open(const std::string &filename);

  void close();

  bool isOpen() const;

  Tag readNextTag();

  Tag peekNextTag();

  bool isAtEnd() const;

private:
  void checkEndianess();

  void readTagFromFile(Tag &tag);

  void swapEndianess(Tag &tag);

  int fileStartKind();

  RelativeEndian mFileEndianess;
  std::ifstream mFileIn;
};

}
#endif //FileEXPLORER_FIFFREADER_HPP
