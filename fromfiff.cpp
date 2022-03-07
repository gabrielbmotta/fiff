
#include "fifftag.hpp"
#include "fiffreader.hpp"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  FiffFile fiffFile(std::string{argv[1]});

  std::cout << "KIND\t\t" << "TYPE\t\t" << "SIZE\t\t" << "NEXT" << "\n";
  while(!fiffFile.isAtEnd())
  {
    auto tag = fiffFile.readNextTag();
    std::cout << tag << "\n";
  }

  return 0;
}
