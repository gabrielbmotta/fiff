#include <fiff/file.hpp>
#include <fiff/idmap.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Fiff::File fiffFile(std::string{argv[1]});
  std::cout << Fiff::Formatting::humanReadable(fiffFile);
  return 0;
}
