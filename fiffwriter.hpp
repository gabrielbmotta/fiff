//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FIFFFILEEXPLORER_FIFFWRITER_HPP
#define FIFFFILEEXPLORER_FIFFWRITER_HPP

#include "fifftag.hpp"
#include "endian.hpp"

#include <string>
#include <fstream>

class FileWriter {
public:
  FileWriter();
  FileWriter(const std::string& filePath);

  void open(const std::string& filePath);
  void close();
  bool isOpen() const;

  void writeTag(const Tag& tag);
private:
  std::ofstream mFileOut;
};

FileWriter::FileWriter()
{

}

FileWriter::FileWriter(const std::string& filePath)
{
  open(filePath);
}

void FileWriter::open(const std::string& filePath)
{
  mFileOut.open(filePath.c_str(), std::ios::binary);
}

void FileWriter::close()
{
  mFileOut.close();
}

bool FileWriter::isOpen() const
{
  return mFileOut.is_open();
}

void FileWriter::writeTag(const Tag& tag)
{
  mFileOut.write(reinterpret_cast<const char*>(&tag.kind), sizeof (tag.kind));
  mFileOut.write(reinterpret_cast<const char*>(&tag.type), sizeof (tag.type));
  mFileOut.write(reinterpret_cast<const char*>(&tag.size), sizeof (tag.size));
  mFileOut.write(reinterpret_cast<const char*>(&tag.next), sizeof (tag.next));
  mFileOut.write(reinterpret_cast<const char*>(tag.data), tag.size);
}

#endif //FIFFFILEEXPLORER_FIFFWRITER_HPP
