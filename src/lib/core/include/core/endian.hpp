//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FIFFFILEEXPLORER_ENDIAN_HPP
#define FIFFFILEEXPLORER_ENDIAN_HPP

#include <algorithm>

enum class Endian{
  unknown,
  little,
  big
};

enum class RelativeEndian{
  same_as_system,
  different_from_system,
  undetermined
};

Endian systemEndian();

template <class T>
void endswap(T *objp)
{
  auto *memp = reinterpret_cast<unsigned char*>(objp);
  std::reverse(memp, memp + sizeof(T));
}

#endif //FIFFFILEEXPLORER_ENDIAN_HPP
