//
// Created by Gabriel Motta on 3/25/22.
//

#include "endian.hpp"

Endian::Absolute systemEndian()
{
  int i = 1;
  if(*(char *)&i == 1)
    return Endian::Absolute::little;
  else
    return Endian::Absolute::big;
}
