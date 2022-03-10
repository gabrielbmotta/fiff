#include <fiff/file.hpp>
#include <fiff/idmap.hpp>
#include <core/commandlineinput.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Fiff::File fiffFile(std::string{argv[1]});

  std::string file;
//  if ()
  Fiff::Formatting formater;

  std::cout << formater.toString(fiffFile);
  return 0;
}
