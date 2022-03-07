//
// Created by Gabriel Motta on 3/7/22.
//

#include "fiff/idmap.hpp"

std::map<int,std::string> Fiff::Formatting::_tagKind
{{100, "FIFF_FILE_ID"},
 {102, "FIFF_DIR_POINTER"},
 {103, "FIFF_BLOCK_ID"},
 {104, "FIFF_BLOCK_START"},
 {105, "FIFF_BLOCK_END"}};

 std::map<int,std::string> Fiff::Formatting::_tagType
 {{3, "int"}};

const std::map<int,std::string>& Fiff::Formatting::tagKinds()
{
  return _tagKind;
}

const std::map<int,std::string>& Fiff::Formatting::tagTypes()
{
  return _tagType;
}

void Fiff::Formatting::replaceIdWithString(std::stringstream& stream,
                         const std::map<int,std::string>& map,
                         int id)
{
  auto mapEntry = map.find(id);
  if (mapEntry != map.end()) {
    stream << mapEntry->second;
  } else {
    stream << id;
  }
}

std::string Fiff::Formatting::humanReadable(const Fiff::Tag& tag){
  std::stringstream out;

  replaceIdWithString(out, _tagKind, tag.kind);
  out << ", data type ";
  replaceIdWithString(out, _tagType, tag.type);
  out << ", ";
  out << tag.size << " bytes, next:" << tag.next;

  return out.str();
}

