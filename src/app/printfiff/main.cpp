#include <fiff/file.hpp>
#include <fiff/idmap.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Fiff::File fiffFile(std::string{argv[1]});

  std::cout << "KIND\t\t" << "TYPE\t\t" << "SIZE\t\t" << "NEXT" << "\n";
  while(!fiffFile.isAtEnd())
  {
    auto tag = fiffFile.readNextTag();
    std::cout << Fiff::Formatting::humanReadable(tag) << "\n";
  }

  return 0;
}
