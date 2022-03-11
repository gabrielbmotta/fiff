#include <fiff/file.hpp>
#include <fiff/idmap.hpp>
#include <core/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Core::CommandLineInput cmdin(argc, argv);
  Fiff::Formatting formater;

  std::string filePath = cmdin.getValueThatEndsWith(".fif");
  if(filePath.empty()){
    std::cerr <<"Could not find file.\n";
    return 1;
  }

  std::string tags = cmdin.getValueForTag("--tags", "-t").second;
  if(!tags.empty()) {
    std::vector tag_set = Core::StringManipulation::getVectorFrom<int>(tags, ',');
    formater.setTagFilter(tag_set);
  }

  Fiff::File fiffFile(filePath);

  std::cout << formater.toString(fiffFile);
  return 0;
}
