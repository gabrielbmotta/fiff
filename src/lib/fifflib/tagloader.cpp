//
// Created by Gabriel Motta on 3/8/22.
//

#include "include/fiff/tagloader.hpp"

Fiff::Tag Fiff::TagLoader::loadNextTag(std::ifstream& stream)
{
  Fiff::Tag tag;

  loadMetaData(tag, stream);
  loadData(tag,stream);

  return tag;
}

void Fiff::TagLoader::loadMetaData(Fiff::Tag &tag, std::ifstream &stream)
{

}

void Fiff::TagLoader::loadData(Fiff::Tag &tag, std::ifstream &stream)
{

}






