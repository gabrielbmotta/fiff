//
// Created by Gabriel Motta on 3/24/22.
//

#include "fiff/output.hpp"

//==============================================================================
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
  auto kind = static_cast<int32_t>(tag.kind);
  auto type = static_cast<int32_t>(tag.type);

  int32_t size = tag.size;

  if (m_relativeEndian == RelativeEndian::different_from_system){
    endswapTagData(tag);

    endswap(&kind);
    endswap(&type);
    endswap(&tag.size);
    endswap(&tag.next);
  }

  //TODO: ability to write in either endianness.
  m_ostream->write(reinterpret_cast<const char*>(&kind), sizeof (kind));
  m_ostream->write(reinterpret_cast<const char*>(&type), sizeof (type));
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
Fiff::Output Fiff::Output::toFile(const std::string &filePath)
{
  Output out;
  out.m_ostream = std::make_unique<std::ofstream>(
          std::ofstream(filePath, std::ios::binary));
  return out;
}

//==============================================================================

Fiff::Output Fiff::Output::toFile(const std::string &filePath, Endian fileEndian)
{
  Output out;
  out.m_ostream = std::make_unique<std::ofstream>(
          std::ofstream(filePath, std::ios::binary));
  out.setEndianess(fileEndian);
  return out;
}

//==============================================================================

void Fiff::Output::setEndianess(Endian fileEndian)
{
  if(systemEndian() == fileEndian){
    m_relativeEndian = RelativeEndian::same_as_system;
  } else {
    m_relativeEndian = RelativeEndian::different_from_system;
  }
}

