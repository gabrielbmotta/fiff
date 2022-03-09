//
// Created by Gabriel Motta on 3/8/22.
//

#include "include/fiff/tagloader.hpp"
#include "include/fiff/datatypes.hpp"

Fiff::TagLoader::TagLoader()
: m_RelativeEndian(RelativeEndian::undetermined)
{
}

void Fiff::TagLoader::determineEndianess(std::ifstream& stream, int expectedId)
{
  std::streampos position = stream.tellg();
  int32_t kind;
  stream.read(reinterpret_cast<char*>(&kind), sizeof(kind));
  if(kind == expectedId){
    m_RelativeEndian = RelativeEndian::same_as_system;
  } else {
    int32_t swappedKind = kind;
    endswap(&swappedKind);
    if(swappedKind == expectedId){
      m_RelativeEndian = RelativeEndian::different_from_system;
    } else {
      promptEndianessFromUser(kind, swappedKind);
    }
  }
  stream.seekg(position);
}

Fiff::Tag Fiff::TagLoader::loadNextTag(std::ifstream& stream)
{
  Fiff::Tag tag;

  loadMetaData(tag, stream);
  loadData(tag,stream);

  return tag;
}

void Fiff::TagLoader::loadMetaData(Fiff::Tag &tag, std::ifstream &stream)
{
  stream.read(reinterpret_cast<char*>(&tag.kind), sizeof(tag.kind));
  stream.read(reinterpret_cast<char*>(&tag.type), sizeof(tag.type));
  stream.read(reinterpret_cast<char*>(&tag.size), sizeof(tag.size));
  stream.read(reinterpret_cast<char*>(&tag.next), sizeof(tag.next));

  if(m_RelativeEndian == RelativeEndian::different_from_system){
    endswap(&tag.kind);
    endswap(&tag.type);
    endswap(&tag.size);
    endswap(&tag.next);
  }
}

void Fiff::TagLoader::loadData(Fiff::Tag &tag, std::ifstream &stream)
{
  switch(tag.type)
  {
    case 3:
    {
      auto *temp = new int32_t;
      stream.read(reinterpret_cast<char *>(temp), tag.size);
      if(m_RelativeEndian == RelativeEndian::different_from_system)
      {
        endswap(temp);
      }
      tag.data = temp;
      break;
    }
    case 30:
    {
    auto temp = new ch_info_rec;
      stream.read(reinterpret_cast<char *>(&temp->scanNo), sizeof(int32_t));
      stream.read(reinterpret_cast<char *>(&temp->logNo), sizeof(int32_t));
      stream.read(reinterpret_cast<char *>(&temp->kind), sizeof(int32_t));
      stream.read(reinterpret_cast<char *>(&temp->range), sizeof(float));
      stream.read(reinterpret_cast<char *>(&temp->cal), sizeof(float));


      stream.read(reinterpret_cast<char *>(temp) + 20, 96-20);
      if(m_RelativeEndian == RelativeEndian::different_from_system)
      {
        endswap(&temp->scanNo);
        endswap(&temp->logNo);
        endswap(&temp->kind);
        endswap(&temp->range);
        endswap(&temp->cal);
      }
      tag.data = temp;
      break;
    }

    default:
    {
      tag.data = new char[tag.size];
      stream.read(reinterpret_cast<char *>(tag.data), tag.size);
    }
  }
}

void Fiff::TagLoader::promptEndianessFromUser(int32_t opt1, int32_t opt2)
{
  int resp = 0;
  std::cout << "Cannot automatically determine endianess of file.\n";
  std::cout << "Please select which looks like the correct tag type of the first tag of the file:\n";
  std::cout << "(1)" << opt1 << ", (2)" << opt2 << "\n";
  std::cin >> resp;

  if(resp == 1){
    m_RelativeEndian = RelativeEndian::same_as_system;
  } else if (resp ==2){
    m_RelativeEndian = RelativeEndian::different_from_system;
  }
}
