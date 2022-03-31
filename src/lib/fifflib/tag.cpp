//
// Created by Gabriel Motta on 3/7/22.
//

#include "include/fiff/tag.hpp"

//==============================================================================
/**
 *
 */
Fiff::Tag::Tag()
{
  kind = 0;
  type = 0;
  size = 0;
  next = 0;
  data = nullptr;
}

//==============================================================================
/**
 *
 * @param other
 */
Fiff::Tag::Tag(const Tag& other)
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

//==============================================================================
/**
 *
 */
Fiff::Tag::~Tag()
{
  if (data)
  {
    delete[] static_cast<char *>(data);
  }
}

//==============================================================================
/**
 *
 * @param rhs
 * @return
 */
Fiff::Tag &Fiff::Tag::operator=(const Fiff::Tag &rhs)
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
