//
// Created by Gabriel Motta on 4/26/22.
//

#include "catch.hpp"

#include "fiff/data.hpp"

TEST_CASE("Data Types", "[data]"){
  char charTest = 'a';
  Fiff::Data charData(charTest);
  REQUIRE(charTest == static_cast<char>(charData));

  int16_t shortTest = 1337;
  Fiff::Data shortData(shortTest);
  REQUIRE(shortTest == static_cast<int16_t>(shortData));

  int32_t intTest = 12345;
  Fiff::Data intData(intTest);
  REQUIRE(intTest == static_cast<int32_t>(intData));

  float_t floatTest = 1357.9f;
  Fiff::Data floatData(floatTest);
  REQUIRE(floatTest == static_cast<float_t>(floatData));

  double_t doubleTest = 246.8;
  Fiff::Data doubleData(doubleTest);
  REQUIRE(doubleTest == static_cast<double_t>(doubleData));

  Fiff::Julian julianTest{};
  julianTest.date = 100;
  Fiff::Data julianData(julianTest);
  REQUIRE(julianTest.date == static_cast<Fiff::Julian>(julianData).date);

  uint16_t ushortTest = 50;
  Fiff::Data ushortData(ushortTest);
  REQUIRE(ushortTest == static_cast<uint16_t>(ushortData));

  uint32_t uintTest = 9000;
  Fiff::Data uintData(uintTest);
  REQUIRE(uintTest == static_cast<uint32_t>(uintData));

  uint64_t ulongTest = 987654321;
  Fiff::Data ulongData(ulongTest);
  REQUIRE(ulongTest == static_cast<uint64_t>(ulongData));

  std::string stringTest = "testint123";
  Fiff::Data stringData(stringTest);
  REQUIRE(stringTest == static_cast<std::string>(stringData));

  int64_t longTest = -9999;
  Fiff::Data longData(longTest);
  REQUIRE(longTest == static_cast<int64_t>(longData));

  std::complex<float_t> compFloatTest = std::complex<float_t>(4.f,5.f);
  Fiff::Data compFloatData(compFloatTest);
  REQUIRE(compFloatTest == static_cast<std::complex<float_t>>(compFloatData));

  std::complex<double> compDoubleTest = std::complex<double_t>(6.,7.);
  Fiff::Data compDoubleData(compDoubleTest);
  REQUIRE(compFloatTest == static_cast<std::complex<float_t>>(compFloatData));

  Fiff::ChannelInfo chInfoTest{
    1,
    2,
    3,
    4.f,
    5.f,
    {1,
    {1.f,2.f,3.f},
    {2.f,3.f,4.f},
    {3.f,4.f,5.f},
    {4.f,5.f,6.f}},
    6,
    7,
    {'a','b','c'}
  };
  Fiff::Data chInfoData(chInfoTest);
  REQUIRE(chInfoTest == static_cast<Fiff::ChannelInfo>(chInfoData));

  Fiff::ID idTest{
    123,
    {1,2},
    1234567,
    3456789
  };
  Fiff::Data idData(idTest);
  REQUIRE(idTest == static_cast<Fiff::ID>(idData));

  Fiff::DirectoryEntry dirTest{
    1,
    2,
    3,
    4
  };
  Fiff::Data dirData(dirTest);
  REQUIRE(dirTest == static_cast<Fiff::DirectoryEntry>(dirData));

  Fiff::DigitizerPoint digpTest{
    1,
    2,
    {3.1f,4.1f,5.1f}
  };
  Fiff::Data digpData(digpTest);
  REQUIRE(digpTest == static_cast<Fiff::DigitizerPoint>(digpData));

  Fiff::ChannelPosition chposTest{1,
                                  {1.f,2.f,3.f},
                                  {2.f,3.f,4.f},
                                  {3.f,4.f,5.f},
                                  {4.f,5.f,6.f}};
  Fiff::Data chposData(chposTest);
  REQUIRE(chposTest == static_cast<Fiff::ChannelPosition>(chposData));

  Fiff::CoordinateTransformation coordTest{
    1,
    2,
    {{{1.f,2.f,3.f}, {4.f,5.f,6.f}, {7.f,8.f,9.f}}},
    {{1,2,3}},
    {{{1.f,2.f,3.f}, {4.f,5.f,6.f}, {7.f,8.f,9.f}}},
    {{1,2,3}}
  };
  Fiff::Data coordData(coordTest);
  REQUIRE(coordTest == static_cast<Fiff::CoordinateTransformation>(coordData));

//  Fiff::DigitizerString digsTest{
//    1,
//    2,
//    3,
//    {{{1,2,3}}, {{2,3,4}}, {{3,4,5}}}
//  };
//  Fiff::Data digsData(digsTest);
//  REQUIRE(digsTest == static_cast<Fiff::DigitizerString>(digsData));

//   Test = ;
//  Fiff::Data Data(Test);
//  REQUIRE(Test == static_cast<>(Data));
}
