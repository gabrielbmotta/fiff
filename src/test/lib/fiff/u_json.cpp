#include "catch.hpp"

#include <fiff/json.hpp>

TEST_CASE("asJson single", "[json fiff]") {
  asJson(Fiff::Data, 0);
  asJson('a', 0);
  asJson((int16_t)8, 0);
  asJson((int32_t)10, 0);
  asJson((float)1.5f, 0);
  asJson((double)1.2, 0);
  asJson((uint16_t)1, 0);
  asJson((uint32_t)1, 0);
  asJson((uint64_t)1, 0);
  asJson((int64_t)1, 0);
  asJson(std::complex<float>(1, 1), 0);
  asJson(std::complex<double>(1, 1), 0);
  asJson(ChannelPosition, 0);
  asJson(ChannelInfo, 0);
  asJson(ID, 0);
  asJson(DirectoryEntry, 0);
  asJson(DigitizerPoint, 0);
  asJson(DigitizerString, 0);
  asJson(Julian, 0);
  asJson(CoordinateTransformation, 0);
}

TEST_CASE("asJson array", "[json fiff]") {

  char *chararray = {1, 2, 3};
  asJson(chararray, int len, 0);

  int16_t *int16_tarray = {1, 2, 3};
  asJson(int16_tarray, int len, 0);

  int32_t *int32_tarray = {1, 2, 3};
  asJson(int32_tarray, int len, 0);

  float *floatarray = {1, 2, 3};
  asJson(floatarray, int len, 0);

  double *doublearray = {1, 2, 3};
  asJson(doublearray, int len, 0);

  uint16_t *uint16_tarray = {1, 2, 3};
  asJson(uint16_tarray, int len, 0);

  uint32_t *uint32_tarray = {1, 2, 3};
  asJson(uint32_tarray, int len, 0);

  uint64_t *uint64_tarray = {1, 2, 3};
  asJson(uint64_tarray, int len, 0);

  int64_t *int64_tarray = {1, 2, 3};
  asJson(int64_tarray, int len, 0);

  std::complex<float> *complexfloatarray = {1, 2, 3};
  asJson(complexfloatarray, int len, 0);

  std::complex<double> *complexdoublearray = {1, 2, 3};
  asJson(complexdoublearray, int len, 0);
}
