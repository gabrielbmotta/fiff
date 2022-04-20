//
// Created by Gabriel Motta on 4/13/22.
//

#include "catch2/catch.hpp"

#include "fiff/input.hpp"
#include "core/endian.hpp"
#include <string>

const std::string testFile = "sample_audvis_trunc_raw.fif";

TEST_CASE("Create input from file", "[input file]")
{
  auto file = Fiff::Input::fromFile(testFile);
}

TEST_CASE("Detect Endianness", "[input file endian]")
{
  auto file = Fiff::Input::fromFile(testFile);
  REQUIRE(file.getEndianess() == Endian::big);
}

TEST_CASE("Set Endianness", "[input file endian]")
{
  auto file1 = Fiff::Input::fromFile(testFile, Endian::little);
  REQUIRE(file1.getEndianess() == Endian::little);
  auto file2 = Fiff::Input::fromFile(testFile, Endian::big);
  REQUIRE(file2.getEndianess() == Endian::big);
}

TEST_CASE("Read tag from input", "[input tag]")
{
  auto file = Fiff::Input::fromFile(testFile);
  auto tag = file.getTag();

  REQUIRE(tag.kind == Fiff::Kind::file_id);
  REQUIRE(tag.type == Fiff::Type::id_struct_);
  REQUIRE(tag.size == 20);

  auto anotherTag = file.getTag();

  REQUIRE(anotherTag.kind == Fiff::Kind::dir_pointer);
  REQUIRE(anotherTag.type == Fiff::Type::int32_);
  REQUIRE(anotherTag.size == 4);
  REQUIRE(static_cast<int32_t>(anotherTag.data) == -1);
}

TEST_CASE("Peek tag from input", "[input tag]")
{
  auto file = Fiff::Input::fromFile(testFile);
  for (int i = 0; i < 3 ; ++i)
  {
    auto tag1 = file.peekTag();
    auto tag2 = file.peekTag();

    REQUIRE(tag1 == tag2);

    auto tag3 = file.getTag();

    REQUIRE(tag1 == tag3);
  }
}

TEST_CASE("Position in input", "[input position]")
{
  auto file = Fiff::Input::fromFile(testFile);

  for (int i = 0; i < 5 ; ++i)
  {
    file.getTag();
  }

  auto firstPos = file.currentReadPosition();
  auto tagAtFirstPos = file.peekTag();

  for (int i = 0; i < 6 ; ++i)
  {
    file.getTag();
  }

  REQUIRE(file.currentReadPosition() != firstPos);
  file.goToReadPosition(firstPos);
  REQUIRE(file.currentReadPosition() == firstPos);
  REQUIRE(file.peekTag() == tagAtFirstPos);

}
