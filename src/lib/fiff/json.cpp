#include "json.hpp"
// #include "formatting.hpp"
#include "input.hpp"
#include "tag.hpp"
#include "data.hpp"
#include "types.hpp"
#include "formatting.hpp"

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

static std::string asJson(const Fiff::Tag&, int indent);
static std::string asJson(const ChannelPosition&, int indent);
static std::string asJson(const ChannelInfo&, int indent);
static std::string asJson(const ID&, int indent);
static std::string asJson(const DirectoryEntry&, int indent);
static std::string asJson(const DigitizerPoint&, int indent);
static std::string asJson(const DigitizerString&, int indent);
static std::string asJson(const Julian&, int indent);
static std::string asJson(const CoordinateTransformation&, int indent);


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

std::string asJson(const Fiff::Tag& tag, int indent){
  std::stringstream stream;

  stream << metaDataAsString(tag) << ", " << dataAsString(tag);

  return stream.str();
}

//==============================================================================
/**
 * Formats channel position object as human-readable string.
 */
std::string asJson(const Fiff::ChannelPosition& pos, int indent)
{
  (void)indent;
  std::stringstream stream;

  stream.precision(2);
  stream << "coil type " << pos.coil_type << ", ";
  stream << "r0 (" << pos.r0[0] << "," << pos.r0[1] << "," << pos.r0[2] << "), ";
  stream << "ex (" << pos.ex[0] << "," << pos.ex[1] << "," << pos.ex[2] << "), ";
  stream << "ey (" << pos.ey[0] << "," << pos.ey[1] << "," << pos.ey[2] << "), ";
  stream << "ez (" << pos.ez[0] << "," << pos.ez[1] << "," << pos.ez[2] << ")";

  return stream.str();
}

//==============================================================================
/**
 * Formats channel info object as human-readable string.
 */
std::string asJson(const Fiff::ChannelInfo& info, int indent)
{
  (void)indent;
  std::stringstream stream;

  stream << std::string(info.ch_name.data()) << ", ";
  stream << "scanNo " << info.scanNo << ", ";
  stream << "logNo " << info.logNo << ", ";
  stream << "kind " << info.kind << ", ";
  stream.precision(2);
  stream << "range " << std::scientific << info.range << ", ";
  stream << "cal " << std::scientific << info.cal << ", ";
  stream << asJson(info.chpos, indent) << ", ";
  stream << "unit " << info.unit << ", ";
  stream << "unit_mul " << info.unit_mul;

  return stream.str();
}

//==============================================================================
/**
 * Formats id object as human-readable string.
 */
std::string asJson(const Fiff::ID &id, int indent)
{
  (void)indent;
  std::stringstream stream;
  stream << "Fiff version " << ((id.version & 0xFFFF0000)>>16) <<"." << (id.version & 0x0000FFFF);
  stream << ", id " << id.machid[0] << " " << id.machid[1];
  stream << ", " << unix_epoch(id.time_sec);

  return stream.str();
}

//==============================================================================
/**
 * Formats directory entry object as human-readable string.
 */
std::string asJson(const Fiff::DirectoryEntry &dirEntr, int indent)
{
  (void)indent;
  (void)dirEntr;
  std::stringstream stream;
  stream << getMapValue(_tagKind, static_cast<int32_t>(dirEntr.kind));
  stream << ", " << getMapValue(_tagType, static_cast<int32_t>(dirEntr.type));
  stream << ", " << dirEntr.size << "B";
  int KB = dirEntr.size/1000;
  int MB = KB/1000;
  if(MB){
    stream << "(" << MB <<  "MB)";
  }  else if (KB){
    stream << "(" << KB <<  "KB)";
  }
  stream << ", position " << dirEntr.position;

  return stream.str();
}

//==============================================================================
/**
 * Formats digitizer position object as human-readable string.
 */
std::string asJson(const Fiff::DigitizerPoint &dig, int indent)
{
  (void)indent;
  std::stringstream stream;
  stream.precision(3);
  stream << dig.kind;
  stream << ", ident " << dig.ident;
  stream << ", (" << dig.r[0] << "," << dig.r[1] << "," << dig.r[2] << ")";
  return stream.str();
}

//==============================================================================
/**
 * Formats digitizer string object as human-readable string.
 */
std::string asJson(const Fiff::DigitizerString &dig, int indent)
{
  (void)indent;
  (void)dig;
  return std::string();
}

//==============================================================================
/**
 * Formats Julian date as human-readable string.
 */
std::string asJson(const Fiff::Julian &jul, int indent)
{
  (void)indent;
  (void)jul;
  return std::string();
}
//==============================================================================
/**
 * Formats Coordinate transformation into human-readable string.
 */
std::string asJson(const Fiff::CoordinateTransformation &coord, int indent)
{
  (void)indent;
  std::stringstream stream;
  stream.precision(3);
  stream << "from " << getMapValue(_coordinateSystem, coord.from) << " to " << getMapValue(_coordinateSystem, coord.to);
  stream << ", rot = ((" << coord.rot[0][0] <<"," << coord.rot[0][1] <<"," << coord.rot[0][2] <<"),(";
  stream << coord.rot[1][0] <<"," << coord.rot[1][1] <<"," << coord.rot[1][2] <<"),(";
  stream << coord.rot[2][0] <<"," << coord.rot[2][1] <<"," << coord.rot[2][2] <<"))";

  stream << ", " << "move = (" << coord.move[0] << "," << coord.move[1] << "," << coord.move[2] << ")";

  return stream.str();
}




