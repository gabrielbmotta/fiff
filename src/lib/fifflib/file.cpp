#include "include/fiff/file.hpp"

Fiff::File::File(const std::string &filename)
        : mFileIn()
        , mFileEndianess(RelativeEndian::undetermined)
{
  open(filename);
  checkEndianess();
}

Fiff::File::File(const std::string &filename, bool sameEndianAsSystem)
        : mFileIn()
{
  if(sameEndianAsSystem){
    mFileEndianess = RelativeEndian::same_as_system;
  } else {
    mFileEndianess = RelativeEndian::different_from_system;
  }
  open(filename);
}

void Fiff::File::open(const std::string &filename)
{
  mFileIn.open(filename.c_str(), std::ios::in | std::ios::binary);
}

void Fiff::File::close()
{
  mFileIn.close();
}

bool Fiff::File::isOpen() const
{
  return mFileIn.is_open();
}

Fiff::Tag Fiff::File::readNextTag()
{
  Fiff::Tag tag;
  readTagFromFile(tag);

  if(mFileEndianess == RelativeEndian::different_from_system)
  {
    swapEndianess(tag);
  }

  tag.data = new char[tag.size];
  mFileIn.read(reinterpret_cast<char*>(tag.data), tag.size);

  return tag;
}

Fiff::Tag Fiff::File::peekNextTag()
{
  std::streampos position = mFileIn.tellg();
  Fiff::Tag tag = readNextTag();
  mFileIn.seekg(position);
  return tag;
}

bool Fiff::File::isAtEnd() const
{
  return mFileIn.eof();
}

void Fiff::File::checkEndianess()
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

void Fiff::File::readTagFromFile(Tag& tag)
{
  mFileIn.read(reinterpret_cast<char*>(&tag.kind), sizeof(tag.kind));
  mFileIn.read(reinterpret_cast<char*>(&tag.type), sizeof(tag.type));
  mFileIn.read(reinterpret_cast<char*>(&tag.size), sizeof(tag.size));
  mFileIn.read(reinterpret_cast<char*>(&tag.next), sizeof(tag.next));
}

void Fiff::File::swapEndianess(Tag& tag)
{
  endswap(&tag.kind);
  endswap(&tag.type);
  endswap(&tag.size);
  endswap(&tag.next);
}


int Fiff::File::fileStartKind()
{
  std::streampos position = mFileIn.tellg();
  int32_t kind;
  mFileIn.read(reinterpret_cast<char*>(&kind), sizeof(kind));
  mFileIn.seekg(position);
  return kind;
}
