//
// Created by Gabriel Motta on 3/8/22.
//

#ifndef FIFFFILEEXPLORER_TAGDATALOADER_HPP
#define FIFFFILEEXPLORER_TAGDATALOADER_HPP

#include "tag.hpp"

#include <io/endian.hpp>
#include <iostream>

namespace Fiff{

class TagLoader
{
  Tag loadNextTag(std::ifstream& stream);

private:
  void loadMetaData(Tag& tag, std::ifstream& stream);
  void loadData(Tag& tag, std::ifstream& stream);

  RelativeEndian endian;
};
}


#endif //FIFFFILEEXPLORER_TAGDATALOADER_HPP
