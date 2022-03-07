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
class Formatting{
public:
  static std::string humanReadable(const Fiff::Tag&);
  static const std::map<int,std::string>& tagKinds();
  static const std::map<int,std::string>& tagTypes();

private:
  static void replaceIdWithString(std::stringstream& stream,
                           const std::map<int,std::string>& map,
                           int id);

  static std::map<int,std::string> _tagKind;
  static std::map<int,std::string> _tagType;
};

}

#endif //FIFFFILEEXPLORER_IDMAP_HPP
