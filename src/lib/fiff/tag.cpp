//
// Created by Gabriel Motta on 4/13/22.
//

#include "fiff/tag.hpp"

#include "core/endian.hpp"

Fiff::Kind Fiff::Tag::getKind()
{
  return Fiff::Kind::req_event;
}

void Fiff::Tag::setKind(Fiff::Kind)
{

}

Fiff::Type Fiff::Tag::getType()
{
  return Fiff::Type::ch_info_struct_;
}

void Fiff::Tag::setType(Fiff::Type)
{

}

void Fiff::Tag::setType(int newType)
{
  type = newType;
}

Fiff::TypeFormat Fiff::Tag::getTypeFormat()
{
  return Fiff::TypeFormat::scalar;
}

void Fiff::Tag::setTypeFormat(Fiff::TypeFormat)
{
}

Fiff::TypeRepresentation Fiff::Tag::getTypeRepresentation()
{
  return Fiff::TypeRepresentation::row_compressed_sparse;
}

void Fiff::Tag::setTypeRepresentation(Fiff::TypeRepresentation)
{

}

int Fiff::Tag::getSize()
{
  return size;
}

void Fiff::Tag::setSize(int newSize)
{
  size = newSize;
}

Fiff::Data &Fiff::Tag::getData()
{
  return data;
}

void Fiff::Tag::setData(Fiff::Data newData)
{
  data = newData;
}

void Fiff::endswapTagData(Tag &tag)
{
  switch(tag.type)
  {
    // 0 bytes
    case Fiff::Type::void_:
    {
      break;
    }
      // 1 byte
    case Fiff::Type::byte_:
    {
      auto *dataPtr = reinterpret_cast<int8_t *>(tag.data.byteArray);
      for(size_t i = 0; i < (tag.size / sizeof (int8_t)); ++i){
        endswap(dataPtr + i);
      }
      break;
    }
      // 2 bytes
    case Fiff::Type::short_:
    case Fiff::Type::ushort_:
    case Fiff::Type::dau_pack13_:
    case Fiff::Type::dau_pack14_:
    case Fiff::Type::dau_pack16_:
    {
      auto *dataPtr = reinterpret_cast<int16_t*>(tag.data.byteArray);
      for(size_t i = 0; i < (tag.size / sizeof (int16_t)); ++i){
        endswap(dataPtr + i);
      }
      break;
    }
      // 4 bytes
    case Fiff::Type::int32_:
    case Fiff::Type::float_:
    case Fiff::Type::julian_:
    case Fiff::Type::uint32_:
    {
      auto *dataPtr = reinterpret_cast<int32_t*>(tag.data.byteArray);
      for(size_t i = 0; i < (tag.size / sizeof (int32_t)); ++i){
        endswap(dataPtr + i);
      }
      break;
    }
      // 8 bytes:
    case Fiff::Type::double_:
    case Fiff::Type::uint64_:
    case Fiff::Type::int64_:
    {
      auto *dataPtr = reinterpret_cast<int64_t*>(tag.data.byteArray);
      for(size_t i = 0; i < (tag.size / sizeof (int64_t)); ++i){
        endswap(dataPtr + i);
      }
      break;
    }
      // array of 1 byte
    case Fiff::Type::string_:
    {
      auto *dataPtr = reinterpret_cast<int8_t*>(tag.data.byteArray);
      for (size_t i = 0; i < (tag.size / sizeof (int8_t)); ++i){
        endswap(dataPtr + i);
      }
      break;
    }
    case Fiff::Type::complex_double_:
    {
      auto* ptr8byte = reinterpret_cast<int64_t*>(tag.data.byteArray);
      for (size_t i = 0; i < (tag.size / sizeof (int64_t)); ++i){
        endswap(ptr8byte + i);
      }
      break;
    }
    case Fiff::Type::old_pack_: // TODO: tricky, variable length
    {
      break;
    }
      // sequential 4 bytes with added array of 1 byte
    case Fiff::Type::ch_info_struct_:
    {
      auto* ptr4byte = reinterpret_cast<int32_t*>(tag.data.byteArray);
      for(int i = 0; i < 20; ++i){
        endswap(ptr4byte + i);
      }
      auto* ptr1byte = reinterpret_cast<int8_t*>(tag.data.byteArray) + 80;
      for(int j = 0; j < 16; ++j){
        endswap(ptr1byte + j);
      }
      break;
    }
      // sequential 4 bytes
    case Fiff::Type::complex_float_:
    case Fiff::Type::id_struct_:
    case Fiff::Type::dir_entry_struct_:
    case Fiff::Type::dig_point_struct_:
    case Fiff::Type::ch_pos_struct_:
    case Fiff::Type::coord_trans_struct_:
    {
      auto* ptr4byte = reinterpret_cast<int32_t*>(tag.data.byteArray);
      for (size_t i = 0; i < (tag.size / sizeof (int32_t)); ++i){
        endswap(ptr4byte + i);
      }
      break;
    }
    case Type::dig_string_struct_:
      break;
    case Type::stream_segment_struct_:
      break;
  }
}
