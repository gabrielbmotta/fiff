#include "json.hpp"
// #include "formatting.hpp"
#include "data.hpp"
#include "formatting.hpp"
#include "input.hpp"
#include "tag.hpp"
#include "types.hpp"

#include <ostream>
#include <string>

using namespace Fiff;

//==============================================================================

std::string fiffTagToJson(Fiff::Tag tag, int &indent_ammout);

void addTagMetaData(std::stringstream &stream, const Fiff::Tag &tag,
                    const char *indent);

void addTagData(std::stringstream &stream, const Fiff::Tag &tag,
                const char *indent);

// void jsonTagToFiff();
//==============================================================================

std::string asJson(Fiff::Data data, int indent_amount);
std::string asJson(char value, int indent_amount);
std::string asJson(char *array, int len, int indent_amount);
std::string asJson(int16_t value, int indent_amount);
std::string asJson(int16_t *array, int len, int indent_amount);
std::string asJson(int32_t value, int indent_amount);
std::string asJson(int32_t *array, int len, int indent_amount);
std::string asJson(float value, int indent_amount);
std::string asJson(float *array, int len, int indent_amount);
std::string asJson(double value, int indent_amount);
std::string asJson(double *array, int len, int indent_amount);
std::string asJson(uint16_t value, int indent_amount);
std::string asJson(uint16_t *array, int len, int indent_amount);
std::string asJson(uint32_t value, int indent_amount);
std::string asJson(uint32_t *array, int len, int indent_amount);
std::string asJson(uint64_t value, int indent_amount);
std::string asJson(uint64_t *array, int len, int indent_amount);
std::string asJson(int64_t value, int indent_amount);
std::string asJson(int64_t *array, int len, int indent_amount);
std::string asJson(std::complex<float> value, int indent_amount);
std::string asJson(std::complex<float> *array, int len, int indent_amount);
std::string asJson(std::complex<double> value, int indent_amount);
std::string asJson(std::complex<double> *array, int len, int indent_amount);
// std::string asJson(const ChannelPosition &, int indent_amount);
// std::string asJson(const ChannelInfo &, int indent_amount);
// std::string asJson(const ID &, int indent_amount);
// std::string asJson(const DirectoryEntry &, int indent_amount);
// std::string asJson(const DigitizerPoint &, int indent_amount);
// std::string asJson(const DigitizerString &, int indent_amount);
// std::string asJson(const Julian &, int indent_amount);
// std::string asJson(const CoordinateTransformation &, int indent_amount);
//
//==============================================================================
/**
 * Creates a json representation of the contents of a fiff file.
 */
void Fiff::fiffToJson(const char *src_path, const char *dest_path) {
  (void)src_path;
  (void)dest_path;

  Fiff::Input input = Fiff::Input::fromFile(src_path);
  std::ofstream output(dest_path, std::ios::out);

  int indent_ammout = 1;
  output << "{\"tags\" : [\n";
  while (!input.atEnd()) {
    output << fiffTagToJson(input.getTag(), indent_ammout);
    if (!input.atEnd()) {
      output << ",\n";
    }
  }

  output << "\n]}\n";
}

// //==============================================================================
// /**
//  *
//  */
// void Fiff::jsonToFiff(const char *src_path, const char *dest_path) {
//   (void)src_path;
//   (void)dest_path;
// }

//==============================================================================
/**
 * Returns json representation of the contents of a fiff tag.
 */
std::string fiffTagToJson(Fiff::Tag tag, int &indent_ammout) {
  std::stringstream stream;
  std::string indent = std::string(indent_ammout * 2, ' ');

  if (tag.kind == Fiff::Kind::block_start) {
    stream << indent << "{\"tags\" : [\n";
    indent = std::string(++indent_ammout * 2, ' ');
  }

  stream << indent << "{\n";
  addTagMetaData(stream, tag, indent.c_str());
  addTagData(stream, tag, indent.c_str());
  stream << indent << "}";

  if (tag.kind == Fiff::Kind::block_end) {
    indent = std::string(--indent_ammout * 2, ' ');
    stream << "\n" << indent << "]}";
  }

  return stream.str();
}

//==============================================================================
/**
 * Appends json formatted fiff tag metadata to a provided stringtream, with the
 * provided indentation.
 */
void addTagMetaData(std::stringstream &stream, const Fiff::Tag &tag,
                    const char *indent) {
  stream << indent << "  \"kind\" : " << tag.kind << ",\n";
  stream << indent << "  \"type\" : " << tag.type << ",\n";
  stream << indent << "  \"size\" : " << tag.size << ",\n";
  stream << indent << "  \"next\" : " << tag.next << ",\n";
}

//==============================================================================
/**
 * Appends json formatted fiff tag data to a provided stringtream, with the
 * provided indentation.
 */
void addTagData(std::stringstream &stream, const Fiff::Tag &tag,
                const char *indent) {
  (void)tag;
  stream << indent << "  \"data\" : "
         << "\"temp_field\""
         << "\n";
}

std::string asJson(Fiff::Data data, int indent_amount) {
  (void)data;
  (void)indent_amount;
  return "data_as_json";
}

std::string asJson(char value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(char *array, int len, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent;
  for (int i = 0; i < len; ++i) {
    str << array[i];
  }
  return str.str();
}

std::string asJson(int16_t value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(int16_t *array, int len, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << "[";
  for (int i = 0; i < len; ++i) {
    str << array[i];
    if (i != len - 1) {
      str << ", ";
    }
  }
  str << "]";
  return str.str();
}

std::string asJson(int32_t value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(int32_t *array, int len, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << "[";
  for (int i = 0; i < len; ++i) {
    str << array[i];
    if (i != len - 1) {
      str << ", ";
    }
  }
  str << "]";
  return str.str();
}

std::string asJson(float value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(float *array, int len, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << "[";
  for (int i = 0; i < len; ++i) {
    str << array[i];
    if (i != len - 1) {
      str << ", ";
    }
  }
  str << "]";
  return str.str();
}

std::string asJson(double value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(double *array, int len, int indent_amount) {}

std::string asJson(uint16_t value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(uint16_t *array, int len, int indent_amount) {}

std::string asJson(uint32_t value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(uint32_t *array, int len, int indent_amount) {}

std::string asJson(uint64_t value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(uint64_t *array, int len, int indent_amount) {}

std::string asJson(int64_t value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(int64_t *array, int len, int indent_amount) {}

std::string asJson(std::complex<float> value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(std::complex<float> *array, int len, int indent_amount) {}

std::string asJson(std::complex<double> value, int indent_amount) {
  std::string indent(indent_amount * 2, ' ');

  std::stringstream str;
  str << indent << value;

  return str.str();
}

std::string asJson(std::complex<double> *array, int len, int indent_amount) {}

//
// //==============================================================================
// /**
//  * Formats channel position object as human-readable string.
//  */
// std::string asJson(const Fiff::ChannelPosition &pos, int indent_amount) {
//   (void)indent;
//   std::stringstream stream;
//
//   stream.precision(2);
//   stream << "coil type " << pos.coil_type << ", ";
//   stream << "r0 (" << pos.r0[0] << "," << pos.r0[1] << "," << pos.r0[2]
//          << "), ";
//   stream << "ex (" << pos.ex[0] << "," << pos.ex[1] << "," << pos.ex[2]
//          << "), ";
//   stream << "ey (" << pos.ey[0] << "," << pos.ey[1] << "," << pos.ey[2]
//          << "), ";
//   stream << "ez (" << pos.ez[0] << "," << pos.ez[1] << "," << pos.ez[2] <<
//   ")";
//
//   return stream.str();
// }
//
// //==============================================================================
// /**
//  * Formats channel info object as human-readable string.
//  */
// std::string asJson(const Fiff::ChannelInfo &info, int indent_amount) {
//   (void)indent;
//   std::stringstream stream;
//
//   stream << std::string(info.ch_name.data()) << ", ";
//   stream << "scanNo " << info.scanNo << ", ";
//   stream << "logNo " << info.logNo << ", ";
//   stream << "kind " << info.kind << ", ";
//   stream.precision(2);
//   stream << "range " << std::scientific << info.range << ", ";
//   stream << "cal " << std::scientific << info.cal << ", ";
//   stream << asJson(info.chpos, indent) << ", ";
//   stream << "unit " << info.unit << ", ";
//   stream << "unit_mul " << info.unit_mul;
//
//   return stream.str();
// }
//
// //==============================================================================
// /**
//  * Formats id object as human-readable string.
//  */
// std::string asJson(const Fiff::ID &id, int indent_amount) {
//   (void)indent;
//   std::stringstream stream;
//   stream << "Fiff version " << ((id.version & 0xFFFF0000) >> 16) << "."
//          << (id.version & 0x0000FFFF);
//   stream << ", id " << id.machid[0] << " " << id.machid[1];
//   // stream << ", " << unix_epoch(id.time_sec);
//
//   return stream.str();
// }
//
// //==============================================================================
// /**
//  * Formats directory entry object as human-readable string.
//  */
// std::string asJson(const Fiff::DirectoryEntry &dirEntr, int indent_amount) {
//   (void)indent;
//   (void)dirEntr;
//
//   return "dir_entry";
// }
//
// //==============================================================================
// /**
//  * Formats digitizer position object as human-readable string.
//  */
// std::string asJson(const Fiff::DigitizerPoint &dig, int indent_amount) {
//   (void)indent;
//   std::stringstream stream;
//   stream.precision(3);
//   stream << dig.kind;
//   stream << ", ident " << dig.ident;
//   stream << ", (" << dig.r[0] << "," << dig.r[1] << "," << dig.r[2] << ")";
//   return stream.str();
// }
//
// //==============================================================================
// /**
//  * Formats digitizer string object as human-readable string.
//  */
// std::string asJson(const Fiff::DigitizerString &dig, int indent_amount) {
//   (void)indent;
//   (void)dig;
//   return std::string();
// }
//
// //==============================================================================
// /**
//  * Formats Julian date as human-readable string.
//  */
// std::string asJson(const Fiff::Julian &jul, int indent_amount) {
//   (void)indent;
//   (void)jul;
//   return std::string();
// }
// //==============================================================================
// /**
//  * Formats Coordinate transformation into human-readable string.
//  */
// std::string asJson(const Fiff::CoordinateTransformation &coord, int
// indent_amount) {
//   (void)indent;
//   (void)coord;
//
//   return "coord";
// }
