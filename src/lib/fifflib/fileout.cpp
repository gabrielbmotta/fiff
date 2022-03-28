//
// Created by Gabriel Motta on 3/24/22.
//

#include "fiff/fileout.hpp"

//==============================================================================
/**
 * Constructs a FileOut object and opens a file at given path, or makes one.
 * @param filename  Path to fiff file to be opened.
 */
Fiff::FileOut::FileOut(const std::string &filePath)
{
  open(filePath);
}

//==============================================================================
/**
 * Opens a file at given path, or makes one.
 * @param filename  Path to fiff file to be opened.
 */
void Fiff::FileOut::open(const std::string &filePath)
{
  m_ofstream.open(filePath, std::ios::binary);
}

//==============================================================================
/**
 * Returns whether the file is open for writting.
 */
bool Fiff::FileOut::isOpen() const
{
  return m_ofstream.is_open();
}

//==============================================================================
/**
 * Writes the given tag to file.
 * @param tag   Tag to be wirtten to file.
 */
void Fiff::FileOut::writeTag(const Fiff::Tag &tag)
{
  //TODO: ability to write in either endianness.
  m_ofstream.write(reinterpret_cast<const char*>(&tag.kind), sizeof (tag.kind));
  m_ofstream.write(reinterpret_cast<const char*>(&tag.type), sizeof (tag.type));
  m_ofstream.write(reinterpret_cast<const char*>(&tag.size), sizeof (tag.size));
  m_ofstream.write(reinterpret_cast<const char*>(&tag.next), sizeof (tag.next));
  m_ofstream.write(reinterpret_cast<const char*>(tag.data), tag.size);
}

//==============================================================================
/**
 * Moves the write head to a position given by input parameter.
 * @param pos   Where to move the write head.
 */
void Fiff::FileOut::goToWritePosition(std::streampos pos)
{
  m_ofstream.seekp(pos);
}

//==============================================================================
/**
 * Gets the current position of the write head.
 */
std::streampos Fiff::FileOut::currentWritePosition()
{
  return m_ofstream.tellp();
}
