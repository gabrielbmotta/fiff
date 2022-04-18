//
// Created by Gabriel Motta on 3/24/22.
//

#include "fiff/output.hpp"

//==============================================================================
/**
 * Constructs an Output object.
 *
 * Prefer a static function that creates an Output to something. (i.e. toFile)
 */
Fiff::Output::Output()
: m_relativeEndian(RelativeEndian::undetermined)
{

}

//==============================================================================
/**
 * Writes the given tag to file.
 * @param tag   Tag to be wirtten to file.
 */
void Fiff::Output::writeTag(Fiff::Tag &tag)
{
  int32_t size = tag.size;

  if (m_relativeEndian == RelativeEndian::different_from_system){
    endswapTagData(tag);
    endswap(&tag.kind);
    endswap(&tag.type);
    endswap(&tag.size);
    endswap(&tag.next);
  }

  m_ostream->write(reinterpret_cast<const char*>(&tag.kind), sizeof (tag.kind));
  m_ostream->write(reinterpret_cast<const char*>(&tag.type), sizeof (tag.type));
  m_ostream->write(reinterpret_cast<const char*>(&tag.size), sizeof (tag.size));
  m_ostream->write(reinterpret_cast<const char*>(&tag.next), sizeof (tag.next));
  m_ostream->write(reinterpret_cast<const char*>(tag.data.byteArray), size);
}

//==============================================================================
/**
 * Moves the write head to a position given by input parameter.
 * @param pos   Where to move the write head.
 */
void Fiff::Output::goToWritePosition(std::streampos pos)
{
  m_ostream->seekp(pos);
}

//==============================================================================
/**
 * Gets the current position of the write head.
 */
std::streampos Fiff::Output::currentWritePosition()
{
  return m_ostream->tellp();
}
//==============================================================================
/**
 * Creates an Output object to write to given file.
 *
 * Creates the file if it does not exist.
 */
Fiff::Output Fiff::Output::toFile(const std::string &filePath)
{
  Output out;
  out.m_ostream = std::make_unique<std::ofstream>(
          std::ofstream(filePath, std::ios::binary));
  return out;
}

//==============================================================================
/**
 * Creates an Output object to write to given file with a selected endianness.
 *
 * Creates the file if it does not exist.
 */
Fiff::Output Fiff::Output::toFile(const std::string &filePath, Endian fileEndian)
{
  Output out;
  out.m_ostream = std::make_unique<std::ofstream>(
          std::ofstream(filePath, std::ios::binary));
  out.setEndianess(fileEndian);
  return out;
}

//==============================================================================
/**
 * Sets the endianness with which the tags will be written.
 */
void Fiff::Output::setEndianess(Endian fileEndian)
{
  if(systemEndian() == fileEndian){
    m_relativeEndian = RelativeEndian::same_as_system;
  } else {
    m_relativeEndian = RelativeEndian::different_from_system;
  }
}

