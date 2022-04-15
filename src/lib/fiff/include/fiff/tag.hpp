//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FIFFFILEEXPLORER_FIFFTAG_HPP
#define FIFFFILEEXPLORER_FIFFTAG_HPP

#include "types.hpp"
#include "data.hpp"
#include <iostream>
#include <cstdint>

namespace Fiff {

struct Tag {
  int kind;   // Tag number.
  int type;   // Data type.
  int32_t size;   // Size of data.
  int32_t next;   // Next object. 0 is sequential, -1 if end of file.
  Data data;   // Pointer to data.
};

void endswapTagData(Tag& tag);
}//namespace

#endif //FIFFFILEEXPLORER_FIFFTAG_HPP
