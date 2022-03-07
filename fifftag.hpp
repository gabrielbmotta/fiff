//
// Created by Gabriel Motta on 3/4/22.
//

#ifndef FIFFFILEEXPLORER_FIFFTAG_HPP
#define FIFFFILEEXPLORER_FIFFTAG_HPP

#include <iostream>
#include <cstdint>

struct Tag {
  int32_t kind;   // Tag number.
  int32_t type;   // Data type.
  int32_t size;   // Size of data.
  int32_t next;   // Next object. 0 is sequential, -1 if end of file.
  void *data;   // Pointer to data.

  Tag();
  Tag(const Tag &);
  ~Tag();

  Tag &operator=(const Tag &rhs);
  friend std::ostream& operator<<(std::ostream& os, const Tag& tag);
};

Tag::Tag()
{
  kind = 0;
  type = 0;
  size = 0;
  next = 0;
  data = nullptr;
}

Tag::Tag(const Tag& other)
{
  kind = other.kind;
  type = other.type;
  size = other.size;
  next = other.next;

  if(other.data && other.size > 0)
  {
    data = new char[size];
    memcpy(data, other.data, static_cast<size_t>(other.size));
  } else {
    data = nullptr;
  }
}

Tag::~Tag()
{
  if (data)
  {
    delete[] static_cast<char *>(data);
  }
}

Tag &Tag::operator=(const Tag &rhs)
{
  if(this != &rhs)
  {
    kind = rhs.kind;
    type = rhs.type;
    size = rhs.size;
    next = rhs.next;

    if(rhs.data && rhs.size > 0)
    {
      if(data)
      {
        delete[] (static_cast<char *>(data));
      }
      data = new char[size];
      memcpy(data, rhs.data, static_cast<size_t>(rhs.size));
    }
  }
  return *this;
}

std::ostream& operator<<(std::ostream& os, const Tag& tag)
{
  os << tag.kind << "\t\t" << tag.type << "\t\t" << tag.size << "\t\t" << tag.next;
  return os;
}

#endif //FIFFFILEEXPLORER_FIFFTAG_HPP
