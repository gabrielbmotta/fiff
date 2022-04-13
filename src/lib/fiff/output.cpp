//
// Created by Gabriel Motta on 3/24/22.
//

#include "fiff/output.hpp"

//==============================================================================
/**
 * Writes the given tag to file.
 * @param tag   Tag to be wirtten to file.
 */
void Fiff::Output::writeTag(Fiff::Tag &tag)
{
  int32_t size = tag.size;
  auto kind = static_cast<int32_t>(tag.kind);
  auto type = static_cast<int32_t>(tag.type);

  if(m_relativeEndian == RelativeEndian::different_from_system){
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
