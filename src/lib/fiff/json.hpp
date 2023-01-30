#ifndef FIFF_LIBFIFF_JSON_HPP
#define FIFF_LIBFIFF_JSON_HPP

namespace Fiff {
void fiffToJson(const char *src_path, const char *dest_path);
void jsonToFiff(const char *src_path, const char *dest_path);

} // namespace Fiff

#endif
