#include "fiff/input.hpp"

#include "fiff/datatypes.hpp"

//==============================================================================
/**
 * Constructs a Input object.
 *
 * Prefer a constructor that also accepts a path to file.
 */
Fiff::Input::Input()
:m_relativeEndian(RelativeEndian::undetermined)
{

}

//==============================================================================
/**
 * Returns next tag in the file, and moves the read head one tag forward.
 */
Fiff::Tag Fiff::Input::readNextTag()
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
Fiff::Tag Fiff::Input::peekNextTag()
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
void Fiff::Input::goToReadPosition(std::streampos pos)
{
  m_istream->seekg(pos);
}

//==============================================================================
/**
 * Gets the current position of the read head.
 */
std::streampos Fiff::Input::currentReadPosition()
{
  return m_istream->tellg();
}

//==============================================================================
/**
 * Returns whether the read head is at the end of the file.
 */
bool Fiff::Input::atEnd()
{
  return m_istream->eof();
}

//==============================================================================

Fiff::Input Fiff::Input::fromFile(const std::string &filePath)
{
  Input in;
  in.m_istream = std::make_unique<std::ifstream>(filePath, std::ios::binary);
  in.setEndianess();
  return in;
}

//==============================================================================

Fiff::Input Fiff::Input::fromFile(const std::string &filePath, Endian fileEndian)
{
  Input in;
  in.m_istream = std::make_unique<std::ifstream>(filePath, std::ios::binary);
  in.setEndianess(fileEndian);
  return in;
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
void Fiff::Input::setEndianess()
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
  if(tag.kind > 1000000 || tag.kind < -1000000){
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
void Fiff::Input::setEndianess(Endian fileEndian)
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
void Fiff::Input::readMetaData(Fiff::Tag &tag)
{
  m_istream->read(reinterpret_cast<char*>(&tag.kind), sizeof(tag.kind));
  m_istream->read(reinterpret_cast<char*>(&tag.type), sizeof(tag.type));
  m_istream->read(reinterpret_cast<char*>(&tag.size), sizeof(tag.size));
  m_istream->read(reinterpret_cast<char*>(&tag.next), sizeof(tag.next));

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
void Fiff::Input::readData(Fiff::Tag &tag)
{
  //TODO: actually sort the endianness of that data in a way that is
  //      not a giant switch statement.
  char* tempData = new char[tag.size];
  m_istream->read(reinterpret_cast<char *>(tempData), tag.size);

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
      auto* dataPtr = reinterpret_cast<Type::ch_info_rec*>(tag.data);
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
