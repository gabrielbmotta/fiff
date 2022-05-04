//
// Created by Gabriel Motta on 3/24/22.
//

#include "output.hpp"

//==============================================================================
/**
 * Constructs an Output object.
 *
 * Prefer a static function that creates an Output to something. (i.e. toFile)
 */
Fiff::Output::Output()
: m_relativeEndian(Endian::Relative::undetermined)
{

}

//==============================================================================
/**
 * Writes the given tag to file.
 * @param tag   Tag to be wirtten to file.
 */
void Fiff::Output::writeTag(const Fiff::Tag &tag)
{
  int32_t size = tag.size;

  if (m_relativeEndian == Endian::Relative::different_from_system){
    auto swapTag = tag;

    endswapTagData(swapTag);
    endswap(&swapTag.kind);
    endswap(&swapTag.type);
    endswap(&swapTag.size);
    endswap(&swapTag.next);

    m_ostream->write(reinterpret_cast<const char*>(&swapTag.kind), sizeof (swapTag.kind));
    m_ostream->write(reinterpret_cast<const char*>(&swapTag.type), sizeof (swapTag.type));
    m_ostream->write(reinterpret_cast<const char*>(&swapTag.size), sizeof (swapTag.size));
    m_ostream->write(reinterpret_cast<const char*>(&swapTag.next), sizeof (swapTag.next));
    m_ostream->write(reinterpret_cast<const char*>(swapTag.data.byteArray), size);
  } else {
    m_ostream->write(reinterpret_cast<const char*>(&tag.kind), sizeof (tag.kind));
    m_ostream->write(reinterpret_cast<const char*>(&tag.type), sizeof (tag.type));
    m_ostream->write(reinterpret_cast<const char*>(&tag.size), sizeof (tag.size));
    m_ostream->write(reinterpret_cast<const char*>(&tag.next), sizeof (tag.next));
    m_ostream->write(reinterpret_cast<const char*>(tag.data.byteArray), size);
  }

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
  out.m_ostream = std::unique_ptr<std::ofstream>(new std::ofstream(filePath, std::ios::binary));
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
  out.m_ostream = std::unique_ptr<std::ofstream>(new std::ofstream(filePath, std::ios::binary));
  out.setEndianess(fileEndian);
  return out;
}

//==============================================================================
/**
 * Sets the endianness with which the tags will be written.
 */
void Fiff::Output::setEndianess(Endian endianness)
{
  if(systemEndian() == endianness){
    m_relativeEndian = Endian::Relative::same_as_system;
  } else {
    m_relativeEndian = Endian::Relative::different_from_system;
  }
}

//==============================================================================
/**
 * Returns the current endianness with which tags wll be written.
 */
Endian Fiff::Output::getEndianess() const
{
  if (m_relativeEndian == Endian::Relative::same_as_system){
    return systemEndian();
  } else if (m_relativeEndian == Endian::Relative::different_from_system){
    if(systemEndian() == Endian::Absolute::little){
      return Endian::Absolute::big;
    } else if(systemEndian() == Endian::Absolute::big){
      return Endian::Absolute::little;
    }
  }
  return Endian::Absolute::unknown;
}

