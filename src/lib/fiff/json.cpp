#include "json.hpp"
// #include "formatting.hpp"
#include "input.hpp"
#include "tag.hpp"

#include <ostream>
#include <string>

//==============================================================================

std::string fiffTagToJson(Fiff::Tag tag, int &indent_ammout);

void addTagMetaData(std::stringstream &stream, const Fiff::Tag &tag,
                    const char *indent);

void addTagData(std::stringstream &stream, const Fiff::Tag &tag,
                const char *indent);

// void jsonTagToFiff();
//==============================================================================

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
