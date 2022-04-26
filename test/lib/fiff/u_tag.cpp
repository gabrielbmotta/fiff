//
// Created by Gabriel Motta on 4/20/22.
//

#include "fiff/tag.hpp"

#include "catch.hpp"


TEST_CASE("Tag Data Endianness Swap 2byte", "[tag endian]"){
  size_t dataSize = sizeof(int16_t);

  int16_t data = 12345;
  Fiff::Tag tag;
  tag.kind = Fiff::Kind::first_sample;
  tag.type = Fiff::Type::short_;
  tag.size = static_cast<int32_t>(dataSize);
  tag.data = data;

  Fiff::endswapTagData(tag);

  auto* tagDataPtr = reinterpret_cast<char*>(tag.data.byteArray);
  auto* dataPtr = reinterpret_cast<char*>(&data);

  bool equal = true;
  for(size_t i = 0; i < dataSize; ++i){
    if(dataPtr[i] != tagDataPtr[dataSize - 1 - i]){
      equal = false;
      break;
    }
  }
  REQUIRE(equal);
}

TEST_CASE("Tag Data Endianness Swap 4 byte", "[tag endian]"){
  size_t dataSize = sizeof(int32_t);

  int32_t data = 12345;
  Fiff::Tag tag;
  tag.kind = Fiff::Kind::first_sample;
  tag.type = Fiff::Type::int32_;
  tag.size = static_cast<int32_t>(dataSize);
  tag.data = data;

  Fiff::endswapTagData(tag);

  auto* tagDataPtr = reinterpret_cast<char*>(tag.data.byteArray);
  auto* dataPtr = reinterpret_cast<char*>(&data);

  bool equal = true;
  for(size_t i = 0; i < dataSize; ++i){
    if(dataPtr[i] != tagDataPtr[dataSize - 1 - i]){
      equal = false;
      break;
    }
  }
  REQUIRE(equal);
}

TEST_CASE("Tag Data Endianness Swap 8byte", "[tag endian]"){
  size_t dataSize = sizeof(int64_t);

  int64_t data = 12345;
  Fiff::Tag tag;
  tag.kind = Fiff::Kind::first_sample;
  tag.type = Fiff::Type::int64_;
  tag.size = static_cast<int32_t>(dataSize);
  tag.data = data;

  Fiff::endswapTagData(tag);

  auto* tagDataPtr = reinterpret_cast<char*>(tag.data.byteArray);
  auto* dataPtr = reinterpret_cast<char*>(&data);

  bool equal = true;
  for(size_t i = 0; i < dataSize; ++i){
    if(dataPtr[i] != tagDataPtr[dataSize - 1 - i]){
      equal = false;
      break;
    }
  }
  REQUIRE(equal);
}
