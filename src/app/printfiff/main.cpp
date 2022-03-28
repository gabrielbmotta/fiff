#include <fiff/input.hpp>
#include <fiff/formatting.hpp>
#include <core/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Core::CommandLineInput cmdin(argc, argv);
  Fiff::Formatting formater;

  if(cmdin.tagExists("--help","-h")){
    std::cout << "|---      printfiff      ---|\n\n"
              << "Usage: printfiff /path/to/file.fif [--tag-kind kind1,kind1,...]\n\n"
              << "-k --tag-kind <input>\t Prints only the tags with matching tag type number.\n\n"
              << "-h --help \t\t Prints help text.\n";
  }


  std::string filePath = cmdin.getValueThatEndsWith(".fif");
  if(filePath.empty()){
    return 0;
  }

  std::string tags = cmdin.getValueForTag("--tag-kind", "-k").second;
  if(!tags.empty()) {
    std::vector tag_set = Core::StringManipulation::getVectorFrom<int>(tags, ',');
    formater.setTagFilter(tag_set);
  }

  Fiff::Input fiffFile(filePath);

  std::cout << formater.toString(fiffFile);
  return 0;
}
