#include "include/fiff/file.hpp"
#include "include/fiff/tagloader.hpp"

Fiff::File::File(const std::string &filename)
        : mFileIn()
        , mTagLoader()
{
  open(filename);
  mTagLoader.determineEndianess(mFileIn, 100);
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
  return mTagLoader.loadNextTag(mFileIn);
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

void Fiff::File::seek(std::streampos pos)
{
  mFileIn.seekg(pos);
}

std::streampos Fiff::File::position()
{
  return mFileIn.tellg();
}
