//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FIFFFILEEXPLORER_FIFFTAG_HPP
#define FIFFFILEEXPLORER_FIFFTAG_HPP

#include <iostream>
#include <cstdint>

namespace Fiff {

struct Tag {
  int32_t kind;   // Tag number.
  int32_t type;   // Data type.
  int32_t size;   // Size of data.
  int32_t next;   // Next object. 0 is sequential, -1 if end of file.
  void *data;   // Pointer to data.

  Tag();

  Tag(const Tag &);

  ~Tag();

  Tag &operator=(const Tag &rhs);

  friend std::ostream &operator<<(std::ostream &os, const Tag &tag);
};
  std::ostream &operator<<(std::ostream &os, const Tag &tag);
}

#endif //FIFFFILEEXPLORER_FIFFTAG_HPP
