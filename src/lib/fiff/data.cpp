//
// Created by Gabriel Motta on 4/7/22.
//

#include <cstdlib>
#include <cstring>
#include "data.hpp"

//==============================================================================
/**
 * Constructs an empty Data object.
 */
Fiff::Data::Data()
        : byteArray(nullptr)
        , size(0)
{
}

//==============================================================================
/**
 * Constructs a copy of a Data object given in the input parameter.
 */
Fiff::Data::Data(const Fiff::Data& other)
        : size(other.size)
{
  if(other.byteArray != nullptr && size > 0){
    byteArray = new char[size];
    memcpy(byteArray, other.byteArray, static_cast<size_t>(other.size));
  } else {
    byteArray = nullptr;
  }
}

//==============================================================================
/**
 * Destroys the data object.
 */
Fiff::Data::~Data()
{
  if (byteArray)
  {
    delete[] static_cast<char *>(byteArray);
  }
}

//==============================================================================
/**
 * Resizes the data object to a new size. This needs to be called if the size of
 * data being stored in the object is being changed.
 */
void Fiff::Data::resize(size_t newSize)
{
  clear();
  this->size = newSize;
  byteArray = new char[this->size];
}

//==============================================================================
/**
 * Clears the data in the object and sets it to a default state.
 */
void Fiff::Data::clear()
{
  if (byteArray)
  {
    delete[] static_cast<char *>(byteArray);
  }
  size = 0;
  byteArray = nullptr;
}

//==============================================================================
/**
 * Creates a Data object from a char.
 */
Fiff::Data::Data(char c)
: byteArray(new char)
, size(1)
{
  *static_cast<char *>(byteArray) = c;
}

//==============================================================================
/**
 * Creates a Data object from a 16 bit int.
 */
Fiff::Data::Data(int16_t number)
: byteArray(new char[2])
, size(2)
{
  *static_cast<int16_t *>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from a 32 bit int.
 */
Fiff::Data::Data(int32_t number)
: byteArray(new char[4])
, size(4)
{
  *static_cast<int32_t*>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from a single precision floating point number.
 */
Fiff::Data::Data(float number)
: byteArray(new char[4])
, size(4)
{
  *static_cast<float_t*>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from a double precision floating point number.
 */
Fiff::Data::Data(double number)
: byteArray(new char[8])
, size(8)
{
  *static_cast<double_t *>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from a Julian date object.
 */
Fiff::Data::Data(Fiff::Julian jul)
: byteArray(new char[4])
, size(4)
{
  *static_cast<int32_t*>(byteArray) = jul.date;
}

//==============================================================================
/**
 * Creates a Data object from an unsigned 16 bit int.
 */
Fiff::Data::Data(uint16_t number)
: byteArray(new char[2])
, size(4)
{
  *static_cast<uint16_t*>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from an unsigned 32 bit int.
 */
Fiff::Data::Data(uint32_t number)
: byteArray(new char[4])
, size(4)
{
  *static_cast<uint32_t*>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from an unsigned 64 bit int.
 */
Fiff::Data::Data(uint64_t number)
: byteArray(new char[8])
, size(8)
{
  *static_cast<uint64_t *>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from a string.
 */
Fiff::Data::Data(const std::string& str)
: byteArray(new char[str.length()])
, size(str.length())
{
  std::memcpy(byteArray, str.c_str(), str.length());
}

//==============================================================================
/**
 * Creates a Data object from a 64 bit int.
 */
Fiff::Data::Data(int64_t number)
: byteArray(new char[8])
, size(8)
{
  *static_cast<int64_t*>(byteArray) = number;
}

//==============================================================================
/**
 * Creates a Data object from a single precision complex floating point number.
 */
Fiff::Data::Data(std::complex<float> num)
: byteArray(new char[8])
, size(8)
{
  auto ptr = static_cast<float_t*>(byteArray);

  *ptr =  num.real();
  *(ptr + 1) = num.imag();
}

//==============================================================================
/**
 * Creates a Data object from a double precision complex floating point number.
 */
Fiff::Data::Data(std::complex<double> num)
        : byteArray(new char[16])
        , size(16)
{
  auto ptr = static_cast<double_t*>(byteArray);

  *ptr =  num.real();
  *(ptr + 1) = num.imag();
}

//==============================================================================
/**
 * Creates a Data object from a Channel Info object.
 */
Fiff::Data::Data(Fiff::ChannelInfo info)
: byteArray(new char[96])
, size(96)
{
  int offset = 0;

  *(static_cast<int32_t*>(byteArray) + offset++) = info.scanNo;
  *(static_cast<int32_t*>(byteArray) + offset++) = info.logNo;
  *(static_cast<int32_t*>(byteArray) + offset++) = info.kind;
  *(static_cast<float*>(byteArray) + offset++) = info.range;
  *(static_cast<float*>(byteArray) + offset++) = info.cal;

  *(static_cast<int32_t*>(byteArray) + offset++) = info.chpos.coil_type;

  *(static_cast<float*>(byteArray) + offset++) = info.chpos.r0[0];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.r0[1];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.r0[2];

  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ex[0];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ex[1];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ex[2];

  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ey[0];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ey[1];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ey[2];

  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ez[0];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ez[1];
  *(static_cast<float*>(byteArray) + offset++) = info.chpos.ez[2];

  *(static_cast<int32_t*>(byteArray) + offset++) = info.unit;
  *(static_cast<int32_t*>(byteArray) + offset++) = info.unit_mul;

  memcpy(static_cast<char*>(byteArray) + offset * sizeof(int32_t), info.ch_name, 16);
}

//==============================================================================
/**
 * Creates a Data object from an Id object.
 */
Fiff::Data::Data(Fiff::ID id)
: byteArray(new char[20])
, size(20)
{
  int offset = 0;

  *(static_cast<int32_t*>(byteArray) + offset++) = id.version;
  *(static_cast<int32_t*>(byteArray) + offset++) = id.machid[0];
  *(static_cast<int32_t*>(byteArray) + offset++) = id.machid[1];
  *(static_cast<int32_t*>(byteArray) + offset++) = id.time_sec;
  *(static_cast<int32_t*>(byteArray) + offset) = id.time_usec;
}

//==============================================================================
/**
 * Creates a Data object from a Directory Entry object.
 */
Fiff::Data::Data(Fiff::DirectoryEntry dir)
: byteArray(new char[16])
, size(16)
{
  int offset = 0;

  *(static_cast<int32_t*>(byteArray) + offset++) = dir.kind;
  *(static_cast<int32_t*>(byteArray) + offset++) = dir.type;
  *(static_cast<int32_t*>(byteArray) + offset++) = dir.size;
  *(static_cast<int32_t*>(byteArray) + offset) = dir.position;
}

//==============================================================================
/**
 * Creates a Data object from a digitizer point object.
 */
Fiff::Data::Data(Fiff::DigitizerPoint dig)
: byteArray(new char[20])
, size(20)
{
  int offset = 0;

  *(static_cast<int32_t*>(byteArray) + offset++) = dig.kind;
  *(static_cast<int32_t*>(byteArray) + offset++) = dig.ident;
  *(static_cast<float*>(byteArray) + offset++) = dig.r[0];
  *(static_cast<float*>(byteArray) + offset++) = dig.r[1];
  *(static_cast<float*>(byteArray) + offset) = dig.r[2];
}

//==============================================================================
/**
 * Creates a Data object from a Channel Position object.
 */
Fiff::Data::Data(Fiff::ChannelPosition chpos)
: byteArray(new char[52])
, size(52)
{
  int offset = 0;

  chpos.coil_type = *(static_cast<int32_t*>(byteArray) + offset++);

  chpos.r0[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.r0[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.r0[2] = *(static_cast<float*>(byteArray) + offset++);

  chpos.ex[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ex[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ex[2] = *(static_cast<float*>(byteArray) + offset++);

  chpos.ey[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ey[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ey[2] = *(static_cast<float*>(byteArray) + offset++);

  chpos.ez[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ez[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ez[2] = *(static_cast<float*>(byteArray) + offset++);
}

//==============================================================================
/**
 * Creates a Data object from a Coordinate Transformation object.
 */
Fiff::Data::Data(Fiff::CoordinateTransformation coord)
: byteArray(new char[104])
, size(104)
{
  int offset = 0;

  *(static_cast<int32_t*>(byteArray) + offset++) = coord.from;
  *(static_cast<int32_t*>(byteArray) + offset++) = coord.to;

  for(auto& row : coord.rot){
    for(auto& element : row)
      *(static_cast<float*>(byteArray) + offset++) = element;
  }

  *(static_cast<float*>(byteArray) + offset++) = coord.move[0];
  *(static_cast<float*>(byteArray) + offset++) = coord.move[1];
  *(static_cast<float*>(byteArray) + offset++) = coord.move[2];

  for(auto& row : coord.invrot){
    for(auto& element : row)
      *(static_cast<float*>(byteArray) + offset++) = element;
  }

  *(static_cast<float*>(byteArray) + offset++) = coord.invmove[0];
  *(static_cast<float*>(byteArray) + offset++) = coord.invmove[1];
  *(static_cast<float*>(byteArray) + offset) = coord.invmove[2];
}

//==============================================================================
/**
 * Creates a Data object from a Digitizer String object.
 */
Fiff::Data::Data(Fiff::DigitizerString)
{

}

//==============================================================================
/**
 * Overloads assignment operator to another Data object.
 */
Fiff::Data &Fiff::Data::operator=(const Fiff::Data &rhs)
{
  if(this != &rhs)
  {
    if(rhs.byteArray && rhs.size > 0)
    {
      size = rhs.size;
      resize(size);
      memcpy(byteArray, rhs.byteArray, static_cast<size_t>(rhs.size));
    } else {
      clear();
    }
  }
  return *this;
}

//==============================================================================
/**
 * Converts the data object into a char.
 */
Fiff::Data::operator char() const
{
  return *static_cast<char*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into a 16 bit int.
 */
Fiff::Data::operator int16_t() const
{
  return *static_cast<int16_t*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into a 32 bit int.
 */
Fiff::Data::operator int32_t() const
{
  return *static_cast<int32_t*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into a single precision floating point number.
 */
Fiff::Data::operator float() const
{
  return *static_cast<float*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into a double precision floating point number.
 */
Fiff::Data::operator double() const
{
  return *static_cast<double*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into a Julian date object.
 */
Fiff::Data::operator Julian() const
{
  Julian j{};
  j.date = *static_cast<int32_t*>(byteArray);
  return j;
}

//==============================================================================
/**
 * Converts the data object into an unsigned 16 bit integer.
 */
Fiff::Data::operator uint16_t() const
{
  return *static_cast<uint16_t*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into an unsigned 32 bit integer.
 */
Fiff::Data::operator uint32_t() const
{
  return *static_cast<uint32_t*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into an unsigned 64 bit integer.
 */
Fiff::Data::operator uint64_t() const
{
  return *static_cast<uint64_t*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into a string.
 */
Fiff::Data::operator std::string() const
{
  return {static_cast<char*>(byteArray), size};
}

//==============================================================================
/**
 * Converts the data object into a 64 bit integer.
 */
Fiff::Data::operator int64_t() const
{
  return *static_cast<int64_t*>(byteArray);
}

//==============================================================================
/**
 * Converts the data object into a single precision floating point number.
 */
Fiff::Data::operator std::complex<float>() const
{
  std::complex<float> f;
  f.real(*static_cast<float*>(byteArray));
  f.imag(*(static_cast<float*>(byteArray) + 1));
  return f;
}

//==============================================================================
/**
 * Converts the data object into a double precision floating point number.
 */
Fiff::Data::operator std::complex<double>() const
{
  std::complex<double> f;
  f.real(*static_cast<double*>(byteArray));
  f.imag(*(static_cast<double*>(byteArray) + 1));
  return f;}

//==============================================================================
/**
 * Converts the data object into a Channel Info object
 */
Fiff::Data::operator ChannelInfo() const
{
  int offset = 0;
  ChannelInfo info{};
  info.scanNo = *(static_cast<int32_t*>(byteArray) + offset++);
  info.logNo = *(static_cast<int32_t*>(byteArray) + offset++);
  info.kind = *(static_cast<int32_t*>(byteArray) + offset++);
  info.range = *(static_cast<float*>(byteArray) + offset++);
  info.cal = *(static_cast<float*>(byteArray) + offset++);

  info.chpos.coil_type = *(static_cast<int32_t*>(byteArray) + offset++);

  info.chpos.r0[0] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.r0[1] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.r0[2] = *(static_cast<float*>(byteArray) + offset++);

  info.chpos.ex[0] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.ex[1] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.ex[2] = *(static_cast<float*>(byteArray) + offset++);

  info.chpos.ey[0] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.ey[1] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.ey[2] = *(static_cast<float*>(byteArray) + offset++);

  info.chpos.ez[0] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.ez[1] = *(static_cast<float*>(byteArray) + offset++);
  info.chpos.ez[2] = *(static_cast<float*>(byteArray) + offset++);

  info.unit = *(static_cast<int32_t*>(byteArray) + offset++);
  info.unit_mul = *(static_cast<int32_t*>(byteArray) + offset++);
  memcpy(info.ch_name, static_cast<char*>(byteArray) + offset * sizeof(int32_t), 16);
  return info;
}

//==============================================================================
/**
 * Converts the data object into a Id object.
 */
Fiff::Data::operator ID() const
{
  int offset = 0;
  ID id{};

  id.version = *(static_cast<int32_t*>(byteArray) + offset++);
  id.machid[0] = *(static_cast<int32_t*>(byteArray) + offset++);
  id.machid[1] = *(static_cast<int32_t*>(byteArray) + offset++);
  id.time_sec = *(static_cast<int32_t*>(byteArray) + offset++);
  id.time_usec = *(static_cast<int32_t*>(byteArray) + offset);

  return id;
}

//==============================================================================
/**
 * Converts the data object into a Directory Entry object.
 */
Fiff::Data::operator DirectoryEntry() const
{
  int offset = 0;
  DirectoryEntry dir{};

  dir.kind = *(static_cast<int32_t*>(byteArray) + offset++);
  dir.type = *(static_cast<int32_t*>(byteArray) + offset++);
  dir.size = *(static_cast<int32_t*>(byteArray) + offset++);
  dir.position = *(static_cast<int32_t*>(byteArray) + offset);

  return dir;
}

//==============================================================================
/**
 * Converts the data object into a Digitizer Point object.
 */
Fiff::Data::operator DigitizerPoint() const
{
  int offset = 0;
  DigitizerPoint dig{};

  dig.kind = *(static_cast<int32_t*>(byteArray) + offset++);
  dig.ident = *(static_cast<int32_t*>(byteArray) + offset++);
  dig.r[0] = *(static_cast<float*>(byteArray) + offset++);
  dig.r[1] = *(static_cast<float*>(byteArray) + offset++);
  dig.r[2] = *(static_cast<float*>(byteArray) + offset);

  return dig;
}

//==============================================================================
/**
 * Converts the data object into a Channel Position object.
 */
Fiff::Data::operator ChannelPosition() const
{
  int offset = 0;
  Fiff::ChannelPosition chpos{};

  chpos.coil_type = *(static_cast<int32_t*>(byteArray) + offset++);

  chpos.r0[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.r0[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.r0[2] = *(static_cast<float*>(byteArray) + offset++);

  chpos.ex[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ex[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ex[2] = *(static_cast<float*>(byteArray) + offset++);

  chpos.ey[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ey[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ey[2] = *(static_cast<float*>(byteArray) + offset++);

  chpos.ez[0] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ez[1] = *(static_cast<float*>(byteArray) + offset++);
  chpos.ez[2] = *(static_cast<float*>(byteArray) + offset);

  return chpos;
}

//==============================================================================
/**
 * Converts the data object into a Coordinate Transformation object.
 */
Fiff::Data::operator CoordinateTransformation() const
{
  int offset = 0;
  CoordinateTransformation coord{};

  coord.from = *(static_cast<int32_t*>(byteArray) + offset++);
  coord.to = *(static_cast<int32_t*>(byteArray) + offset++);

  for(auto& row : coord.rot){
    for(auto& element : row)
      element = *(static_cast<float*>(byteArray) + offset++);
  }

  coord.move[0] = *(static_cast<float*>(byteArray) + offset++);
  coord.move[1] = *(static_cast<float*>(byteArray) + offset++);
  coord.move[2] = *(static_cast<float*>(byteArray) + offset++);

  for(auto& row : coord.invrot){
    for(auto& element : row)
      element = *(static_cast<float*>(byteArray) + offset++);
  }

  coord.invmove[0] = *(static_cast<float*>(byteArray) + offset++);
  coord.invmove[1] = *(static_cast<float*>(byteArray) + offset++);
  coord.invmove[2] = *(static_cast<float*>(byteArray) + offset);

  return coord;
}

//==============================================================================
/**
 * Converts the data object into a Digitizer String object.
 */
Fiff::Data::operator DigitizerString() const
{
  int offset = 0;

  DigitizerString dig_str;

  dig_str.kind = *(static_cast<int32_t*>(byteArray) + offset++);
  dig_str.ident = *(static_cast<int32_t*>(byteArray) + offset++);
  dig_str.npoints = *(static_cast<int32_t*>(byteArray) + offset++);

  dig_str.rr.reserve(dig_str.npoints);
  for(int i = 0; i < dig_str.npoints; ++i){
    dig_str.rr.push_back({*(static_cast<float_t *>(byteArray) + offset++),
                          *(static_cast<float_t *>(byteArray) + offset++),
                          *(static_cast<float_t *>(byteArray) + offset++)});
  }

  return {};
}

bool Fiff::Data::operator==(const Fiff::Data &other) const
{
  if (this->size == other.size){
    for(size_t i = 0; i < this->size; ++i){
      if(static_cast<char*>(this->byteArray)[i] != static_cast<char*>(other.byteArray)[i]){
        return false;
      }
    }
    return true;
  }
  return false;
}
