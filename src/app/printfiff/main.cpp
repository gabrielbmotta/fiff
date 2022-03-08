#include <fiff/file.hpp>
#include <fiff/idmap.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Fiff::File fiffFile(std::string{argv[1]});
  Fiff::Formatting::humanReadablePrint(fiffFile);

  return 0;
}
