//
// Created by Gabriel Motta on 3/7/22.
//

#ifndef FIFFFILEEXPLORER_IDMAP_HPP
#define FIFFFILEEXPLORER_IDMAP_HPP

#include "tag.hpp"

#include <string>
#include <sstream>
#include <map>

namespace Fiff {
std::stringstream humanReadable(const Fiff::Tag&);
}

#endif //FIFFFILEEXPLORER_IDMAP_HPP
