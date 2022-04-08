//
// Created by Gabriel Motta on 4/7/22.
//

#ifndef FIFFFILEEXPLORER_DATA_HPP
#define FIFFFILEEXPLORER_DATA_HPP

#endif //FIFFFILEEXPLORER_DATA_HPP

#include "types.hpp"

#include <cstdint>
#include <climits>
#include <string>
#include <complex>

namespace Fiff{

struct ChannelPosition {
  int32_t coil_type;
  float r0[3];
  float ex[3];
  float ey[3];
  float ez[3];
}; //mSize is 48 bytes

struct ChannelInfo {
  int32_t scanNo;       /**< Position of this channel in scanning order. */
  int32_t logNo;        /**< Logical channel number. These must be unique within channels of the same kind. */
  int32_t kind;         /**< Kind of the channel described (MEG, EEG, EOG, etc.) */
  float range;          /**< The raw data values must be multiplied by this to get into volts at the electronics output. */
  float cal;            /**< Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul. */
  ChannelPosition chpos;       /**< Channel position. */
  int32_t unit;         /**< The real-world unit-of measure. */
  int32_t unit_mul;     /**< The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul. */
  char ch_name[16];     /**< Descriptive name for the channel. */
}; //mSize is 96 bytes

struct ID {
  int32_t version;
  int32_t machid[2];
  int32_t time_sec;
  int32_t time_usec;
};//total mSize is 20 bytes

struct DirectoryEntry{
  Kind kind;
  Type type;
  int32_t size;
  int32_t position;
};

struct DigitizerPoint{
  int32_t kind;
  int32_t ident;
  float r[3];
};

struct DigitizerString{
  int32_t kind;
  int32_t ident;
  int32_t npoints;
  float* rr[3];
};

struct CoordinateTransformation{
  int32_t from;
  int32_t to;
  float rot[3][3];
  float move[3];
  float invrot[3][3];
  float invmove[3];
};

//struct ch_info_t {
//  int32_t scanNo;       /**< Position of this channel in scanning order. */
//  int32_t logNo;        /**< Logical channel number. These must be unique within channels of the same kind. */
//  int32_t kind;         /**< Kind of the channel described (MEG, EEG, EOG, etc.) */
//  float range;          /**< The raw data values must be multiplied by this to get into volts at the electronics output. */
//  float cal;            /**< Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul. */
//  int32_t coil_type;    /**< Kind of MEG coil or kind of EEG channel. */
//  float r0[3];          /**< Coil coordinate system origin. For EEG electrodes, this is the location of the electrode. */
//  float ex[3];          /**< Coil coordinate system unit vector ex. For EEG electrodes, this specifies the location of a reference electrode. Set to (0,0,0) for no reference. */
//  float ey[3];          /**< Coil coordinate system unit vector ey. This is ignored for EEG electrodes. */
//  float ez[3];          /**< Coil coordinate system unit vector ez . This is ignored for EEG electrodes. */
//  int32_t unit;         /**< The real-world unit-of measure. */
//  int32_t unit_mul;     /**< The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul. */
//}; //mSize is 80 bytes

struct Julian{
  int32_t date;
};

struct Data {
  Data();
  Data(const Data &);
  ~Data();
  Data &operator=(const Data &rhs);

  void resize(size_t newSize);
  void clear();

  Data(char); // 1
  Data(int16_t); // 2
  Data(int32_t); // 3
  Data(float); // 4
  Data(double); // 5
  Data(Julian); // 6
  Data(uint16_t); // 7
  Data(uint32_t); // 8
  Data(uint64_t); // 9
  Data(std::string); // 10
  Data(int64_t); // 11
  Data(std::complex<float>); // 20
  Data(std::complex<double>); // 21
  Data(ChannelInfo); // 30
  Data(ID); // 31
  Data(DirectoryEntry); // 32
  Data(DigitizerPoint); // 33
  Data(ChannelPosition); // 34
  Data(CoordinateTransformation); // 35
  Data(DigitizerString); // 36

  operator char() const; // 1
  operator int16_t() const; // 2
  operator int32_t() const; // 3
  operator float() const; // 4
  operator double() const; // 5
  operator Julian() const; // 6
  operator uint16_t() const; // 7
  operator uint32_t() const; // 8
  operator uint64_t() const; // 9
  operator std::string() const; // 10
  operator int64_t() const; // 11
  operator std::complex<float>() const; // 20
  operator std::complex<double>() const; // 21
  operator ChannelInfo() const; // 30
  operator ID() const; // 31
  operator DirectoryEntry() const; // 32
  operator DigitizerPoint() const; // 33
  operator ChannelPosition() const; // 34
  operator CoordinateTransformation() const; // 35
  operator DigitizerString() const; // 36

  size_t size;
  void* byteArray;
};

}
