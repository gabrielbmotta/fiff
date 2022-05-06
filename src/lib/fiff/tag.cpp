//
// Created by Gabriel Motta on 4/13/22.
//

#include "tag.hpp"

#include "../core/endian.hpp"

//==============================================================================
/**
 *
 * @param other
 * @return
 */
bool Fiff::Tag::operator==(const Fiff::Tag &other) const
{
  return(this->kind == other.kind &&
         this->type == other.type &&
         this->size == other.size &&
         this->data == other.data);
}

//==============================================================================
/**
 * Swaps the endianness of a tag's data.
 */
void Fiff::endswapTagData(Tag &tag)
{
  switch((tag.type) & Fiff::Type::baseMask)
  {
    // 0 bytes / 1 byte
    case Fiff::Type::void_:
    case Fiff::Type::byte_:
    case Fiff::Type::string_:
    {
      break;
    }
      // 2 bytes
    case Fiff::Type::short_:
    case Fiff::Type::ushort_:
    case Fiff::Type::dau_pack13_:
    case Fiff::Type::dau_pack14_:
    case Fiff::Type::dau_pack16_:
    {
      int16_t* dataPtr = reinterpret_cast<int16_t*>(tag.data.byteArray);
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
      int32_t* dataPtr = reinterpret_cast<int32_t*>(tag.data.byteArray);
      for(size_t i = 0; i < (tag.size / sizeof (int32_t)); ++i){
        endswap(dataPtr + i);
      }
      break;
    }
      // 8 bytes:
    case Fiff::Type::double_:
    case Fiff::Type::uint64_:
    case Fiff::Type::int64_:
    case Fiff::Type::complex_double_:
    {
      int64_t* dataPtr = reinterpret_cast<int64_t*>(tag.data.byteArray);
      for(size_t i = 0; i < (tag.size / sizeof (int64_t)); ++i){
        endswap(dataPtr + i);
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
      int32_t* ptr4byte = reinterpret_cast<int32_t*>(tag.data.byteArray);
      for(int i = 0; i < 20; ++i){
        endswap(ptr4byte + i);
      }
      int8_t* ptr1byte = reinterpret_cast<int8_t*>(tag.data.byteArray) + 80;
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
      int32_t* ptr4byte = reinterpret_cast<int32_t*>(tag.data.byteArray);
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
