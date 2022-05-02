//
// Created by Gabriel Motta on 4/7/22.
//

#ifndef FIFFFILEEXPLORER_DATA_HPP
#define FIFFFILEEXPLORER_DATA_HPP

#include "types.hpp"

#include <cstdint>
#include <climits>
#include <string>
#include <complex>
#include <vector>
#include <array>

namespace Fiff{

//==============================================================================
/**
 * Object containing the position of a channel.
 */
struct ChannelPosition {
  int32_t coil_type;
  std::array<float,3> r0;
  std::array<float,3> ex;
  std::array<float,3> ey;
  std::array<float,3> ez;

  bool operator==(const ChannelPosition& other) const;
}; //mSize is 48 bytes

//==============================================================================
/**
 * Object containing information about a channel.
 */
struct ChannelInfo {
  int32_t scanNo;       /**< Position of this channel in scanning order. */
  int32_t logNo;        /**< Logical channel number. These must be unique within channels of the same kind. */
  int32_t kind;         /**< Kind of the channel described (MEG, EEG, EOG, etc.) */
  float range;          /**< The raw data values must be multiplied by this to get into volts at the electronics output. */
  float cal;            /**< Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul. */
  ChannelPosition chpos;       /**< Channel position. */
  int32_t unit;         /**< The real-world unit-of measure. */
  int32_t unit_mul;     /**< The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul. */
  std::array<char,16> ch_name;     /**< Descriptive name for the channel. */

  bool operator==(const ChannelInfo& other) const;
}; //mSize is 96 bytes

//==============================================================================
/**
 * Object containing identifying information about the source of a fiff file.
 */
struct ID {
  int32_t version;
  std::array<int32_t,2> machid;
  int32_t time_sec;
  int32_t time_usec;

  bool operator==(const ID& other) const;
};//total mSize is 20 bytes

//==============================================================================
/**
 * An entry showing where to find elements in a fiff file.
 */
struct DirectoryEntry{
  int32_t kind;
  int32_t type;
  int32_t size;
  int32_t position;

  bool operator==(const DirectoryEntry& other) const;
};

//==============================================================================
/**
 * An object containing the position of a digitization point.
 */
struct DigitizerPoint{
  int32_t kind;
  int32_t ident;
  std::array<float,3> r;

  bool operator==(const DigitizerPoint& other) const;
};

//==============================================================================
/**
 * An object containing a series of positions of digitization points.
 */
struct DigitizerString{
  int32_t kind;
  int32_t ident;
  int32_t npoints;
  std::vector<std::array<float,3>> rr;

  bool operator==(const DigitizerString& other) const;
};

//==============================================================================
/**
 * An object containing transformations between coordinate spaces.
 */
struct CoordinateTransformation{
  int32_t from;
  int32_t to;
  std::array<std::array<float,3>,3> rot;
  std::array<float,3> move;
  std::array<std::array<float,3>,3> invrot;
  std::array<float,3> invmove;

  bool operator==(const CoordinateTransformation& other) const;
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

//==============================================================================
/**
 * An object containing a date in the julian format.
 */
struct Julian{
  int32_t date;

  bool operator==(const Julian& other) const;
};

//==============================================================================
/**
 * An object that holds fiff data.
 */
struct Data {
  Data();
  Data(const Data &);
  ~Data();
  Data &operator=(const Data &rhs);

  void resize(size_t newSize);
  void clear();

  explicit Data(char); // 1
  explicit Data(int16_t); // 2
  explicit Data(int32_t); // 3
  explicit Data(float); // 4
  explicit Data(double); // 5
  explicit Data(Julian); // 6
  explicit Data(uint16_t); // 7
  explicit Data(uint32_t); // 8
  explicit Data(uint64_t); // 9
  explicit Data(const std::string&); // 10
  explicit Data(int64_t); // 11
  explicit Data(std::complex<float>); // 20
  explicit Data(std::complex<double>); // 21
  explicit Data(ChannelInfo); // 30
  explicit Data(ID); // 31
  explicit Data(DirectoryEntry); // 32
  explicit Data(DigitizerPoint); // 33
  explicit Data(ChannelPosition); // 34
  explicit Data(CoordinateTransformation); // 35
  explicit Data(DigitizerString); // 36

  explicit operator char() const; // 1
  explicit operator int16_t() const; // 2
  explicit operator int32_t() const; // 3
  explicit operator float() const; // 4
  explicit operator double() const; // 5
  explicit operator Julian() const; // 6
  explicit operator uint16_t() const; // 7
  explicit operator uint32_t() const; // 8
  explicit operator uint64_t() const; // 9
  explicit operator std::string() const; // 10
  explicit operator int64_t() const; // 11
  explicit operator std::complex<float>() const; // 20
  explicit operator std::complex<double>() const; // 21
  explicit operator ChannelInfo() const; // 30
  explicit operator ID() const; // 31
  explicit operator DirectoryEntry() const; // 32
  explicit operator DigitizerPoint() const; // 33
  explicit operator ChannelPosition() const; // 34
  explicit operator CoordinateTransformation() const; // 35
  explicit operator DigitizerString() const; // 36

  void* byteArray;

  bool operator==(const Data& other) const;
private:
  size_t size;

};
}

#endif //FIFFFILEEXPLORER_DATA_HPP
