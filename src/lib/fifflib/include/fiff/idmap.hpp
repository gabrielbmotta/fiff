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
#include <unordered_set>
#include <vector>

namespace Fiff {
class Formatting{
public:
  static std::string fullTagAsString(const Fiff::Tag&);
  static std::string fullFileAsString(Fiff::File&);

  std::string toString(const Fiff::Tag&);
  std::string toString(Fiff::File&);

  static const std::map<int,std::string>& tagKinds();
  static const std::map<int,std::string>& tagTypes();

  void setTagFilter(const std::vector<int>&);

private:
  static std::string getMapValue(const std::map<int,std::string>& map,
                                 int id);

  static std::string formatTagMetaData(const Fiff::Tag& tag);
  static std::string formatTagData(const Fiff::Tag& tag);

  static std::map<int,std::string> _tagKind;
  static std::map<int,std::string> _tagType;
  static std::map<int,std::string> _blockID;

  std::vector<int> m_tagFilter;
};
}

#endif //FIFFFILEEXPLORER_IDMAP_HPP
