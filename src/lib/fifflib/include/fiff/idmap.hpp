//
// Created by Gabriel Motta on 3/7/22.
//

#ifndef FIFFFILEEXPLORER_IDMAP_HPP
#define FIFFFILEEXPLORER_IDMAP_HPP

#include "tag.hpp"
#include "file.hpp"
#include <io/endian.hpp>

#include <string>
#include <sstream>
#include <map>

namespace Fiff {
class Formatting{
public:
  static std::string humanReadable(const Fiff::Tag&);
  static std::string humanReadable(Fiff::File&);

  static const std::map<int,std::string>& tagKinds();
  static const std::map<int,std::string>& tagTypes();

private:
  static std::string getMapValue(const std::map<int,std::string>& map,
                                 int id);

  static std::string formatTagMetaData(const Fiff::Tag& tag);
  static std::string formatTagData(const Fiff::Tag& tag);

  static std::map<int,std::string> _tagKind;
  static std::map<int,std::string> _tagType;
  static std::map<int,std::string> _blockID;
};

}

#endif //FIFFFILEEXPLORER_IDMAP_HPP
