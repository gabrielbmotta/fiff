#include "json.hpp"
// #include "formatting.hpp"
#include "input.hpp"
#include "tag.hpp"

#include <ostream>
#include <string>

std::string fiffTagToJson(Fiff::Tag tag);
// void jsonTagToFiff();

void Fiff::fiffToJson(const char *src_path, const char *dest_path) {
  (void)src_path;
  (void)dest_path;

  Fiff::Input input = Fiff::Input::fromFile(src_path);
  std::ofstream output(dest_path, std::ios::out);

  output << "{\"tags\" : [\n";
  while (!input.atEnd()) {
    output << fiffTagToJson(input.getTag());
    if (!input.atEnd()) {
      output << ",\n";
    }
  }

  output << "\n]}\n";
}

void Fiff::jsonToFiff(const char *src_path, const char *dest_path) {
  (void)src_path;
  (void)dest_path;
}

std::string fiffTagToJson(Fiff::Tag tag) {

  std::stringstream stream;
  static int indent_ammout = 1;
  std::string indent = std::string(indent_ammout * 2, ' ');

  if (tag.kind == Fiff::Kind::block_start) {
    stream << indent << "{\"tags\" : [\n";
    ++indent_ammout;
    indent = std::string(indent_ammout * 2, ' ');
  }

  stream << indent << "{\n";
  stream << indent << "  \"kind\" : " << tag.kind << ",\n";
  stream << indent << "  \"type\" : " << tag.type << ",\n";
  stream << indent << "  \"size\" : " << tag.size << ",\n";
  stream << indent << "  \"next\" : " << tag.next << "\n";
  stream << indent << "}";

  if (tag.kind == Fiff::Kind::block_end) {
    --indent_ammout;
    indent = std::string(indent_ammout * 2, ' ');
    stream << "\n" << indent << "]}";
  }

  return stream.str();
}
