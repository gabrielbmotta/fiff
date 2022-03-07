//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FIFFFILEEXPLORER_FIFFREADER_HPP
#define FIFFFILEEXPLORER_FIFFREADER_HPP

#include "fifftag.hpp"
#include "endian.hpp"

#include <fstream>
#include <string>

class FiffFile {
public:
  FiffFile(): mFileIn() , mFileEndianess(RelativeEndian::undetermined){};
  explicit FiffFile(const std::string &filename);
  explicit FiffFile(const std::string &filename, bool sameEndianAsSystem);

  void open(const std::string &filename);
  void close();
  bool isOpen() const;

  Tag readNextTag();
  Tag peekNextTag();

  bool isAtEnd() const;

private:
  void checkEndianess();
  void readTagFromFile(Tag& tag);
  void swapEndianess(Tag& tag);
  int fileStartKind();

  RelativeEndian mFileEndianess;
  std::ifstream mFileIn;
};

FiffFile::FiffFile(const std::string &filename)
: mFileIn()
, mFileEndianess(RelativeEndian::undetermined)
{
  open(filename);
  checkEndianess();
}

FiffFile::FiffFile(const std::string &filename, bool sameEndianAsSystem)
: mFileIn()
{
  if(sameEndianAsSystem){
    mFileEndianess = RelativeEndian::same_as_system;
  } else {
    mFileEndianess = RelativeEndian::different_from_system;
  }
  open(filename);
}

void FiffFile::open(const std::string &filename)
{
  mFileIn.open(filename.c_str(), std::ios::in | std::ios::binary);
}

void FiffFile::close()
{
  mFileIn.close();
}

bool FiffFile::isOpen() const
{
  return mFileIn.is_open();
}

Tag FiffFile::readNextTag()
{
  Tag tag;
  readTagFromFile(tag);

  if(mFileEndianess == RelativeEndian::different_from_system)
  {
    swapEndianess(tag);
  }

  tag.data = new char[tag.size];
  mFileIn.read(reinterpret_cast<char*>(tag.data), tag.size);

  return tag;
}

Tag FiffFile::peekNextTag()
{
  std::streampos position = mFileIn.tellg();
  Tag tag = readNextTag();
  mFileIn.seekg(position);
  return tag;
}

bool FiffFile::isAtEnd() const
{
  return mFileIn.eof();
}

void FiffFile::checkEndianess()
{
  mFileEndianess = RelativeEndian::undetermined;
  int32_t kind = fileStartKind();

  if(kind == 100)
  {
    mFileEndianess = RelativeEndian::same_as_system;
    return;
  }
  endswap(&kind);
  if(kind == 100)
  {
    mFileEndianess = RelativeEndian::different_from_system;\
    return;
  }
}

void FiffFile::readTagFromFile(Tag& tag)
{
  mFileIn.read(reinterpret_cast<char*>(&tag.kind), sizeof(tag.kind));
  mFileIn.read(reinterpret_cast<char*>(&tag.type), sizeof(tag.type));
  mFileIn.read(reinterpret_cast<char*>(&tag.size), sizeof(tag.size));
  mFileIn.read(reinterpret_cast<char*>(&tag.next), sizeof(tag.next));
}

void FiffFile::swapEndianess(Tag& tag)
{
  endswap(&tag.kind);
  endswap(&tag.type);
  endswap(&tag.size);
  endswap(&tag.next);
}


int FiffFile::fileStartKind()
{
  std::streampos position = mFileIn.tellg();
  int32_t kind;
  mFileIn.read(reinterpret_cast<char*>(&kind), sizeof(kind));
  mFileIn.seekg(position);
  return kind;
}

#endif //FIFFFILEEXPLORER_FIFFREADER_HPP
