//
// Created by Gabriel Motta on 3/7/22.
//

#ifndef FIFFFILEEXPLORER_FORMATTING_HPP
#define FIFFFILEEXPLORER_FORMATTING_HPP

#if (__cplusplus >= 201103L)

#include "tag.hpp"
#include "input.hpp"
#include "../core/endian.hpp"

#include <string>
#include <sstream>
#include <map>
#include <unordered_set>
#include <vector>

namespace Fiff {
class Formatting{
public:
  static std::string asString(const Fiff::Tag&);
  static std::string asString(const ChannelPosition&);
  static std::string asString(const ChannelInfo&);
  static std::string asString(const ID&);
  static std::string asString(const DirectoryEntry&);
  static std::string asString(const DigitizerPoint&);
  static std::string asString(const DigitizerString&);
  static std::string asString(const Julian&);
  static std::string asString(const CoordinateTransformation&);

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
  static const std::map<int,std::string> _coordinateSystem;

};
}
#endif
#endif //FIFFFILEEXPLORER_FORMATTING_HPP
