//
// Created by Gabriel Motta on 3/8/22.
//

#ifndef FIFFFILEEXPLORER_TAGDATALOADER_HPP
#define FIFFFILEEXPLORER_TAGDATALOADER_HPP

#include "tag.hpp"

#include <io/endian.hpp>
#include <iostream>
#include <fstream>

namespace Fiff{

class TagLoader
{
public:
  TagLoader();
  void determineEndianess(std::ifstream& stream, int expectedId);

  Tag loadNextTag(std::ifstream& stream);

private:
  void loadMetaData(Tag& tag, std::ifstream& stream);
  void loadData(Tag& tag, std::ifstream& stream);

  void promptEndianessFromUser(int32_t opt1, int32_t opt2);

  RelativeEndian m_RelativeEndian;
};
}


#endif //FIFFFILEEXPLORER_TAGDATALOADER_HPP
