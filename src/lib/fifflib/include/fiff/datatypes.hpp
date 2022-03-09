//
// Created by Gabriel Motta on 3/8/22.
//

#ifndef FIFFFILEEXPLORER_DATATYPES_HPP
#define FIFFFILEEXPLORER_DATATYPES_HPP

namespace Fiff {

// Type Structs
struct ch_info_t {
  int32_t scanNo;       // Position of this channel in scanning order.
  int32_t logNo;        // Logical channel number. These must be unique within channels of the same kind.
  int32_t kind;         // Kind of the channel described (MEG, EEG, EOG, etc.)
  float range;          // The raw data values must be multiplied by this to get into volts at the electronics output.
  float cal;            // Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul.
  int32_t coil_type;    // Kind of MEG coil or kind of EEG channel.
  float r0[3];          // Coil coordinate system origin. For EEG electrodes, this is the location of the electrode.
  float ex[3];          // Coil coordinate system unit vector ex. For EEG electrodes, this specifies the location of a reference electrode. Set to (0,0,0) for no reference.
  float ey[3];          // Coil coordinate system unit vector ey. This is ignored for EEG electrodes.
  float ez[3];          // Coil coordinate system unit vector ez . This is ignored for EEG electrodes.
  int32_t unit;         // The real-world unit-of measure.
  int32_t unit_mul;     // The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul.
}; //mSize is 80 bytes

struct ch_pos_t {
  int32_t coil_type;
  float r0[3];
  float ex[3];
  float ey[3];
  float ez[3];
}; //mSize is 48 bytes

struct ch_info_rec {
  int32_t scanNo;       // Position of this channel in scanning order.
  int32_t logNo;        // Logical channel number. These must be unique within channels of the same kind.
  int32_t kind;         // Kind of the channel described (MEG, EEG, EOG, etc.)
  float range;          // The raw data values must be multiplied by this to get into volts at the electronics output.
  float cal;            // Calibration of the channel. If the raw data values are multiplied by range*cal, the result is in units given by unit and unit_mul.
  ch_pos_t chpos;  // Channel position.
  int32_t unit;         // The real-world unit-of measure.
  int32_t unit_mul;     // The unit multiplier. The result given by range*cal*data is in units unit*10^unit_mul.
  char ch_name[16];     // Descriptive name for the channel.
}; //mSize is 96 bytes

struct id_t {
  int32_t version;
  int32_t machid[2];
  int32_t time_sec;
  int32_t time_usec;
};//total mSize is 20 bytes

}
#endif //FIFFFILEEXPLORER_DATATYPES_HPP
