#include "input.hpp"

#include "types.hpp"

//==============================================================================
/**
 * Constructs a Input object.
 *
 * Prefer a static function that creates an Input from a source (i.e. fromFile)
 */
Fiff::Input::Input()
:m_relativeEndian(Endian::undetermined)
,m_istream(NULL)
{

}

//==============================================================================
/**
 * Destructs the Input object.
 */
Fiff::Input::~Input()
{
  delete m_istream;
}

//==============================================================================
/**
 * Returns next tag in the file, and moves the read head one tag forward.
 */
Fiff::Tag Fiff::Input::getTag()
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
Fiff::Tag Fiff::Input::peekTag()
{
  std::streampos position = currentReadPosition();
  Fiff::Tag tag = getTag();
  goToReadPosition(position);
  return tag;
}

//==============================================================================

void Fiff::Input::skipTag()
{
  m_istream->seekg(2 * sizeof(int32_t), std::ios::cur);

  int32_t size;
  m_istream->read(reinterpret_cast<char*>(&size), sizeof(int32_t));

  if(m_relativeEndian == Endian::different_from_system)
  {
    endswap(&size);
  }

  m_istream->seekg(sizeof(int32_t) + size, std::ios::cur);
}

//==============================================================================

int32_t Fiff::Input::peekKind()
{
  return getMetaDataElementAtOffset(0);
}

//==============================================================================

int32_t Fiff::Input::peekType()
{
  return getMetaDataElementAtOffset(sizeof(int32_t));
}

//==============================================================================

int32_t Fiff::Input::peekSize()
{
  return getMetaDataElementAtOffset(2 * sizeof(int32_t));
}

//==============================================================================

int32_t Fiff::Input::peekNext()
{
  return getMetaDataElementAtOffset(3 * sizeof(int32_t));
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
std::streampos Fiff::Input::currentReadPosition() const
{
  return m_istream->tellg();
}

//==============================================================================
/**
 * Returns whether the read head is at the end of the file.
 */
bool Fiff::Input::atEnd() const
{
  return (m_istream->eof() || m_istream->peek() == std::ifstream::traits_type::eof());
}

//==============================================================================
/**
 * Creates an object to read from a fiff file tag by tag.
 */
Fiff::Input Fiff::Input::fromFile(const std::string &filePath)
{
  Input in;
  in.m_istream = new std::ifstream(filePath, std::ios::binary);
  in.setEndianess();
  return in;
}

//==============================================================================
/**
 * Creates an object to read from a fiff file tag by tag, with a user
 * specified endianess.
 */
Fiff::Input Fiff::Input::fromFile(const std::string &filePath, Endian::Absolute fileEndian)
{
  Input in;
  in.m_istream = new std::ifstream(filePath, std::ios::binary);
  in.setEndianess(fileEndian);
  return in;
}

//==============================================================================
/**
 * Returns the endianness of the files.
 */
Endian::Absolute Fiff::Input::getEndianess() const
{
  if (m_relativeEndian == Endian::same_as_system){
    return systemEndian();
  } else if (m_relativeEndian == Endian::different_from_system){
    if(systemEndian() == Endian::little){
      return Endian::big;
    } else if(systemEndian() == Endian::big){
      return Endian::little;
    }
  }
  return Endian::unknown;
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
  std::streampos pos = m_istream->tellg();
  int32_t kind = 0;
  m_istream->read(reinterpret_cast<char*>(&kind), sizeof(kind));
  if(kind == 100) {
    m_relativeEndian = Endian::same_as_system;
    m_istream->seekg(pos);
    return;
  }

  int32_t swapkind = kind;
  endswap(&swapkind);
  if(swapkind == 100) {
    m_relativeEndian = Endian::different_from_system;
    m_istream->seekg(pos);
    return;
  }

  // fallback test if file does not begin with correct tag
  if(kind > 1000000 || kind < -1000000){
    m_relativeEndian = Endian::different_from_system;
  } else {
    m_relativeEndian = Endian::same_as_system;
  }
  m_istream->seekg(pos);
}

//==============================================================================
/**
 * Determines the file's endianness based on user input.
 * @param fileEndian    Endianness of the file.
 */
void Fiff::Input::setEndianess(Endian::Absolute fileEndian)
{
  if(systemEndian() == fileEndian){
    m_relativeEndian = Endian::same_as_system;
  } else {
    m_relativeEndian = Endian::different_from_system;
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

  if(m_relativeEndian == Endian::different_from_system){
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
  //TODO: check time of switch statement vs function map vs other possible implementations
  tag.data.resize(tag.size);
  m_istream->read(reinterpret_cast<char *>(tag.data.byteArray), tag.size);

  if(m_relativeEndian == Endian::different_from_system)
  {
    endswapTagData(tag);
  }
}

//==============================================================================

int Fiff::Input::getMetaDataElementAtOffset(int offset)
{
  int32_t element;

  std::streampos originalPosition = m_istream->tellg();
  m_istream->seekg(offset, std::ios::cur);

  m_istream->read(reinterpret_cast<char*>(&element), sizeof(int32_t));
  m_istream->seekg(originalPosition);

  if(m_relativeEndian == Endian::different_from_system)
  {
    endswap(&element);
  }

  return element;
}
