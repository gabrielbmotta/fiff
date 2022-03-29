//
// Created by Gabriel Motta on 3/7/22.
//

#ifndef FIFFFILEEXPLORER_FORMATTING_HPP
#define FIFFFILEEXPLORER_FORMATTING_HPP

#include "fiff/tag.hpp"
#include "fiff/input.hpp"
#include <core/endian.hpp>

#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <vector>

namespace Fiff {
class Formatting{
public:
  static std::string asString(const Fiff::Tag&);

  static const std::map<int,std::string>& tagKinds();
  static const std::map<int,std::string>& tagTypes();
  static const std::map<int,std::string>& blockIds();

private:
  static std::string getMapValue(const std::map<int,std::string>& map,
                                 int id);

  static std::string formatTagMetaData(const Fiff::Tag& tag);
  static std::string formatTagData(const Fiff::Tag& tag);

  static const std::map<int,std::string> _tagKind;
  static const std::map<int,std::string> _tagType;
  static const std::map<int,std::string> _blockID;
};
}

#endif //FIFFFILEEXPLORER_FORMATTING_HPP
