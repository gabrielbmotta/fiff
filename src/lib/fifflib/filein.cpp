//
// Created by Gabriel Motta on 3/24/22.
//

#include "fiff/filein.hpp"

#include "fiff/datatypes.hpp"

//==============================================================================
/**
 * Constructs a FileIn object.
 *
 * Prefer a constructor that also accepts a path to file.
 */
Fiff::FileIn::FileIn()
:m_relativeEndian(RelativeEndian::undetermined)
{

}

//==============================================================================
/**
 * Constructs a FileIn object and opens a file at the path passed to it.
 * @param filename  Path to fiff file to be opened.
 *
 * Endianness will be determined automatically.
 */
Fiff::FileIn::FileIn(const std::string &filename)
{
  open(filename);
}

//==============================================================================
/**
 * Constructs a FileIn object and opens a file at the path passed to it.
 * @param filePath  Path to fiff file to be opened.
 * @param fileEndian    Endianess of file to be opened.
 *
 * Endianness will not be determined automatically. Prefer a call that does
 * it automatically to this.
 */
Fiff::FileIn::FileIn(const std::string &filePath, Endian fileEndian)
{
  open(filePath, fileEndian);
}

//==============================================================================
/**
 * Opens a fiff file at the given path.
 * @param filePath  Path to fiff file to be opened.
 *
 * Endianness will be determined automatically.
 */
void Fiff::FileIn::open(const std::string &filePath)
{
  m_ifstream.open(filePath.c_str(), std::ios::binary);
  setEndianess();
}

//==============================================================================
/**
 * Opens a file at the path passed to it.
 * @param filePath  Path to fiff file to be opened.
 * @param fileEndian    Endianess of file to be opened.
 *
 * Endianness will not be determined automatically. Prefer a call that does
 * it automatically to this.
 */
void Fiff::FileIn::open(const std::string &filePath, Endian fileEndian)
{
  open(filePath);
  setEndianess(fileEndian);
}

//==============================================================================
/**
 * Returns whether the file is open for reading.
 */
bool Fiff::FileIn::isOpen() const
{
  return m_ifstream.is_open();
}

//==============================================================================
/**
 * Returns next tag in the file, and moves the read head one tag forward.
 */
Fiff::Tag Fiff::FileIn::readNextTag()
{
  Fiff::Tag tag;

  readMetaData(tag);
  readData(tag);

  return tag;
}

//==============================================================================
/**
 * Returns next tag in the file. Read head does not move.
 */
Fiff::Tag Fiff::FileIn::peekNextTag()
{
  std::streampos position = currentReadPosition();
  Fiff::Tag tag = readNextTag();
  goToReadPosition(position);
  return tag;
}

//==============================================================================
/**
 * Moves the read head to a position given by input parameter.
 * @param pos   Where to move the read head.
 */
void Fiff::FileIn::goToReadPosition(std::streampos pos)
{
  m_ifstream.seekg(pos);
}

//==============================================================================
/**
 * Gets the current position of the read head.
 */
std::streampos Fiff::FileIn::currentReadPosition()
{
  return m_ifstream.tellg();
}

//==============================================================================
/**
 * Returns whether the read head is at the end of the file.
 */
bool Fiff::FileIn::atEnd()
{
  return m_ifstream.eof();
}

//==============================================================================
/**
 * Tries to determine the file's endianness by peeking at the next tag.
 * Call this function when read position is at start.
 *
 * This function is ideally looking for tag with id 100, which by convention
 * is at the start of a fiff file. If it does not find that when checking both
 * endian possibilities, it checks which endianness produces a tag kind in a
 * "reasonable" range, ie. not in the millions.
 */
void Fiff::FileIn::setEndianess()
{
  Tag tag = peekNextTag();
  if(tag.kind == 100) {
    m_relativeEndian = RelativeEndian::same_as_system;
    return;
  }

  int swapkind = tag.kind;
  endswap(&swapkind);
  if(tag.kind == 100) {
    m_relativeEndian = RelativeEndian::different_from_system;
    return;
  }

  // fallback test if file does not begin with correct tag
  if(tag.kind > 1000000 || tag.kind < 1000000){
    m_relativeEndian = RelativeEndian::different_from_system;
  } else {
    m_relativeEndian = RelativeEndian::same_as_system;
  }
}

//==============================================================================
/**
 * Determines the file's endianness based on user input.
 * @param fileEndian    Endianness of the file.
 */
void Fiff::FileIn::setEndianess(Endian fileEndian)
{
  if (systemEndian() == fileEndian){
    m_relativeEndian = RelativeEndian::same_as_system;
  } else {
    m_relativeEndian = RelativeEndian::different_from_system;
  }
}

//==============================================================================
/**
 * Reads tag metadata and adds it to a tag, swapping endianness if needed.
 * @param tag   Tag object where the read data will be placed.
 */
void Fiff::FileIn::readMetaData(Fiff::Tag &tag)
{
  m_ifstream.read(reinterpret_cast<char*>(&tag.kind), sizeof(tag.kind));
  m_ifstream.read(reinterpret_cast<char*>(&tag.type), sizeof(tag.type));
  m_ifstream.read(reinterpret_cast<char*>(&tag.size), sizeof(tag.size));
  m_ifstream.read(reinterpret_cast<char*>(&tag.next), sizeof(tag.next));

  if(m_relativeEndian == RelativeEndian::different_from_system){
    endswap(&tag.kind);
    endswap(&tag.type);
    endswap(&tag.size);
    endswap(&tag.next);
  }
}

//==============================================================================
/**
 * Reads tag data and adds it to a tag, swapping endianness if needed.
 * @param tag   Tag object where the read data will be placed.
 *
 * This function assumes that the tag object has populated size and type
 * fields, used to determine how many bytes to read in and how to flip data
 * endianness if necessary.
 *
 * This function assumes the read head is at the data portion of a fiff tag
 * in the stream.
 *
 * Because some data types are structs, we need to swap bytes of each field
 * individually.
 */
void Fiff::FileIn::readData(Fiff::Tag &tag)
{
  //TODO: actually sort the endianness of that data in a way that is
  //      not a giant switch statement.
  char* tempData = new char[tag.size];
  m_ifstream.read(reinterpret_cast<char *>(tempData), tag.size);

  switch(tag.type){
    case 3:
    {
      auto* dataPtr = reinterpret_cast<int32_t*>(tag.data);
      if(m_relativeEndian == RelativeEndian::different_from_system)
      {
        endswap(dataPtr);
      }
      break;
    }
    case 30:
    {
      auto* dataPtr = reinterpret_cast<ch_info_rec*>(tag.data);
      if(m_relativeEndian == RelativeEndian::different_from_system)
      {
        endswap(&dataPtr->scanNo);
        endswap(&dataPtr->logNo);
        endswap(&dataPtr->kind);
        endswap(&dataPtr->range);
        endswap(&dataPtr->cal);
      }
      break;
    }
  }

}
