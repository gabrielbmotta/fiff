//
// Created by Gabriel Motta on 4/18/22.
//

#include "catch.hpp"

#include "../../../src/lib/fiff/output.hpp"
#include "../../../src/lib/core/endian.hpp"

#include <iostream>

static const auto testKind = Fiff::Kind::first_sample;
static const auto testType = Fiff::Type::int32_;
static const auto testSize = 4;
static const auto testNext = 0;
static const auto testData = 12345;

static Fiff::Tag testTag()
{
  Fiff::Tag tag;
  tag.kind = testKind;
  tag.type = testType;
  tag.size = testSize;
  tag.next = testNext;
  tag.data.resize(4);
  tag.data = static_cast<int32_t>(testData);
  return tag;
}

TEST_CASE("Create output to file", "[output file]")
{
  auto file = Fiff::Output::toFile("test_create.fif");

  std::ifstream check("test_create.fif");

  REQUIRE(check.is_open());
}

TEST_CASE("Write tag", "[output tag]")
{
  {
    auto file = Fiff::Output::toFile("test_write.fif");
    Fiff::Tag tag = testTag();
    file.writeTag(tag);
  }
  std::ifstream check("test_write.fif", std::ios::binary);

  char readbuff[std::max({sizeof testKind, sizeof testType, sizeof testSize, sizeof testNext, sizeof testData})];

  check.read(readbuff, sizeof testKind);
  auto kind = *static_cast<int32_t *>(static_cast<void*>(readbuff));
  REQUIRE(kind == testKind);

  check.read(readbuff, sizeof testType);
  auto type = *static_cast<int32_t *>(static_cast<void*>(readbuff));
  REQUIRE(type == testType);

  check.read(readbuff, sizeof testSize);
  auto size = *static_cast<int32_t *>(static_cast<void*>(readbuff));
  REQUIRE(size == testSize);

  check.read(readbuff, sizeof testData);
  auto next = *static_cast<int32_t *>(static_cast<void*>(readbuff));
  REQUIRE(next == testNext);

  check.read(readbuff, 4);
  auto data = *static_cast<int32_t *>(static_cast<void*>(readbuff));
  REQUIRE(data == testData);
}

TEST_CASE("Set endianess", "[output file endianess]")
{
  {
    auto fileBE1 = Fiff::Output::toFile("BE1.fif", Endian::big);
    auto fileBE2 = Fiff::Output::toFile("BE2.fif");
    fileBE2.setEndianess(Endian::big);
    auto fileLE1 = Fiff::Output::toFile("LE1.fif", Endian::little);
    auto fileLE2 = Fiff::Output::toFile("LE2.fif");
    fileLE2.setEndianess(Endian::little);

    Fiff::Tag tag = testTag();

    fileBE1.writeTag(tag);
    fileBE2.writeTag(tag);
    fileLE1.writeTag(tag);
    fileLE2.writeTag(tag);
  }

  std::ifstream checkBE1("BE1.fif", std::ios::binary);
  char readBE1[std::max({sizeof testKind, sizeof testType, sizeof testSize, sizeof testNext, sizeof testData})];
  checkBE1.read(readBE1, sizeof testKind);
  auto kindBE1 = *static_cast<int32_t *>(static_cast<void*>(readBE1));

  std::ifstream checkBE2("BE2.fif", std::ios::binary);
  char readBE2[std::max({sizeof testKind, sizeof testType, sizeof testSize, sizeof testNext, sizeof testData})];
  checkBE2.read(readBE2, sizeof testKind);
  auto kindBE2 = *static_cast<int32_t *>(static_cast<void*>(readBE2));

  std::ifstream checkLE1("LE1.fif", std::ios::binary);
  char readLE1[std::max({sizeof testKind, sizeof testType, sizeof testSize, sizeof testNext, sizeof testData})];
  checkLE1.read(readLE1, sizeof testKind);
  auto kindLE1 = *static_cast<int32_t *>(static_cast<void*>(readLE1));

  std::ifstream checkLE2("LE2.fif", std::ios::binary);
  char readLE2[std::max({sizeof testKind, sizeof testType, sizeof testSize, sizeof testNext, sizeof testData})];
  checkLE2.read(readLE2, sizeof testKind);
  auto kindLE2 = *static_cast<int32_t *>(static_cast<void*>(readLE2));

  REQUIRE(kindBE1 == kindBE2);
  REQUIRE(kindLE1 == kindLE2);
  REQUIRE(kindBE1 != kindLE1);
  REQUIRE(((kindBE1 == testKind) || (kindLE1 == testKind)));

  auto endswapKindBE = kindBE1;
  endswap(&endswapKindBE);
  auto endswapKindLE = kindLE1;
  endswap(&endswapKindLE);

  REQUIRE(((endswapKindBE == testKind) || (endswapKindLE == testKind)));
}

TEST_CASE("Position in output", "[output position]")
{

}
