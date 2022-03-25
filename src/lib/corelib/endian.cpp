//
// Created by Gabriel Motta on 3/25/22.
//

#include "core/endian.hpp"

Endian systemEndian()
{
  int i = 1;
  if(*(char *)&i == 1)
    return Endian::little;
  else
    return Endian::big;
}