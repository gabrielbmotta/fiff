#include <fiff/input.hpp>
#include <fiff/formatting.hpp>
#include <core/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Core::CommandLineInput cmdin(argc, argv);

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

  std::vector<int> tag_set;
  if(!tags.empty()) {
    tag_set = Core::StringManipulation::getVectorFrom<int>(tags, ',');
  }

  auto inFile = Fiff::Input::fromFile(filePath);

  std::string padding = "    ";
  int indent = 0;

  while(!inFile.atEnd()){
    auto tag = inFile.getTag();
    if(!tag_set.empty() &&  std::find(tag_set.begin(), tag_set.end(), static_cast<int32_t>(tag.kind)) == tag_set.end()){
      continue;
    }

    if (tag.kind == Fiff::Kind::block_end){
      --indent;
    }
    for (int i = 0 ; i < indent ; ++i){
      std::cout << padding;
    }
    std::cout << Fiff::Formatting::asString(tag);
    std::cout << "\n";
    if(tag.kind == Fiff::Kind::block_start){
      ++indent;
    }
  }

  return 0;
}
