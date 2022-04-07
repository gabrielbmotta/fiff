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

void Fiff::Data::resize(int newSize)
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

Fiff::Data::operator char()
{
  return 0;
}

Fiff::Data::operator int16_t()
{
  return 0;
}

Fiff::Data::operator int32_t()
{
  return 0;
}

Fiff::Data::operator float()
{
  return 0;
}

Fiff::Data::operator double()
{
  return 0;
}

Fiff::Data::operator Julian()
{
  return Fiff::Julian();
}

Fiff::Data::operator uint16_t()
{
  return 0;
}

Fiff::Data::operator uint32_t()
{
  return 0;
}

Fiff::Data::operator uint64_t()
{
  return 0;
}

Fiff::Data::operator std::string()
{
  return std::string();
}

Fiff::Data::operator int64_t()
{
  return 0;
}

Fiff::Data::operator std::complex<float>()
{
  return std::complex<float>();
}

Fiff::Data::operator std::complex<double>()
{
  return std::complex<double>();
}

Fiff::Data::operator ChannelInfo()
{
  return Fiff::ChannelInfo();
}

Fiff::Data::operator ID()
{
  return Fiff::ID();
}

Fiff::Data::operator DirectoryEntry()
{
  return Fiff::DirectoryEntry();
}

Fiff::Data::operator DigitizerPoint()
{
  return Fiff::DigitizerPoint();
}

Fiff::Data::operator ChannelPosition()
{
  return Fiff::ChannelPosition();
}

Fiff::Data::operator DigitizerString()
{
  return Fiff::DigitizerString();
}
