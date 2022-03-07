//
// Created by Gabriel Motta on 3/7/22.
//

#include "fiff/idmap.hpp"

const std::map<int,std::string>& tagKind()
{
  static std::map<int,std::string> _tagKind
  {{100, "FIFF_FILE_ID"},
   {102, "FIFF_DIR_POINTER"},
   {103, "FIFF_BLOCK_ID"},
   {104, "FIFF_BLOCK_START"},
   {105, "FIFF_BLOCK_END"}};

  return _tagKind;
}

const std::map<int,std::string>& tagType()
{
  static std::map<int,std::string> _tagType
  {{3, "int"}};

  return _tagType;
}

void replaceIdWithString(std::stringstream& stream,
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

std::stringstream Fiff::humanReadable(const Fiff::Tag& tag){
  std::stringstream out;

  replaceIdWithString(out, tagKind(), tag.kind);
  out << "\t\t";
  replaceIdWithString(out, tagType(), tag.type);
  out << "\t\t";
  out << tag.size << "\t\t" << tag.next;

  return out;
}

