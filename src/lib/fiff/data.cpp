//
// Created by Gabriel Motta on 4/7/22.
//

#include <cstdlib>
#include <cstring>
#include "fiff/data.hpp"

Fiff::Data::Data()
        : size(0)
        , byteArray(nullptr)
{
}

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

Fiff::Data::~Data()
{
  if (byteArray)
  {
    delete[] static_cast<char *>(byteArray);
  }
}

void Fiff::Data::resize(size_t newSize)
{
  clear();
  this->size = newSize;
  byteArray = new char[this->size];
}

void Fiff::Data::clear()
{
  if (byteArray)
  {
    delete[] static_cast<char *>(byteArray);
  }
  size = 0;
  byteArray = nullptr;
}


Fiff::Data::Data(char)
{

}

Fiff::Data::Data(int16_t)
{

}

Fiff::Data::Data(int32_t)
{

}

Fiff::Data::Data(float)
{

}

Fiff::Data::Data(double)
{

}

Fiff::Data::Data(Fiff::Julian)
{

}

Fiff::Data::Data(uint16_t)
{

}

Fiff::Data::Data(uint32_t)
{

}

Fiff::Data::Data(uint64_t)
{

}

Fiff::Data::Data(std::string)
{

}

Fiff::Data::Data(int64_t)
{

}

Fiff::Data::Data(std::complex<float>)
{

}

Fiff::Data::Data(std::complex<double>)
{

}

Fiff::Data::Data(Fiff::ChannelInfo)
{

}

Fiff::Data::Data(Fiff::ID)
{

}

Fiff::Data::Data(Fiff::DirectoryEntry)
{

}

Fiff::Data::Data(Fiff::DigitizerPoint)
{

}

Fiff::Data::Data(Fiff::ChannelPosition)
{

}

Fiff::Data::Data(Fiff::CoordinateTransformation)
{

}

Fiff::Data::Data(Fiff::DigitizerString)
{

}

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

Fiff::Data::operator char() const
{
  return *static_cast<char*>(byteArray);
}

Fiff::Data::operator int16_t() const
{
  return *static_cast<int16_t*>(byteArray);
}

Fiff::Data::operator int32_t() const
{
  return *static_cast<int32_t*>(byteArray);
}

Fiff::Data::operator float() const
{
  return *static_cast<float*>(byteArray);
}

Fiff::Data::operator double() const
{
  return *static_cast<double*>(byteArray);
}

Fiff::Data::operator Julian() const
{
  Julian j{};
  j.date = *static_cast<int32_t*>(byteArray);
  return j;
}

Fiff::Data::operator uint16_t() const
{
  return *static_cast<uint16_t*>(byteArray);
}

Fiff::Data::operator uint32_t() const
{
  return *static_cast<uint32_t*>(byteArray);
}

Fiff::Data::operator uint64_t() const
{
  return *static_cast<uint64_t*>(byteArray);
}

Fiff::Data::operator std::string() const
{
  return {static_cast<char*>(byteArray), size};
}

Fiff::Data::operator int64_t() const
{
  return *static_cast<int64_t*>(byteArray);
}

Fiff::Data::operator std::complex<float>() const
{
  std::complex<float> f;
  f.real(*static_cast<float*>(byteArray));
  f.imag(*(static_cast<float*>(byteArray) + 1));
  return f;
}

Fiff::Data::operator std::complex<double>() const
{
  std::complex<double> f;
  f.real(*static_cast<double*>(byteArray));
  f.imag(*(static_cast<double*>(byteArray) + 1));
  return f;}

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

Fiff::Data::operator CoordinateTransformation() const
{
  int offset = 0;
  CoordinateTransformation coord{};

  coord.from = *(static_cast<int32_t*>(byteArray) + offset++);
  coord.from = *(static_cast<int32_t*>(byteArray) + offset++);

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

Fiff::Data::operator DigitizerString() const
{
  return {};
}
