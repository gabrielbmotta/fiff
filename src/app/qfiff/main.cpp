//
// Created by Gabriel Motta on 3/10/22.
//

#include <core/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include <fiff/idmap.hpp>

#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Core::CommandLineInput cmdin(argc, argv);
  std::map<int,std::string> map;
  std::string user_input;

  auto kind_input = cmdin.getValueForTag("--tag-kind", "-k");
  auto type_input = cmdin.getValueForTag("--data-type", "-t");
  auto block_input = cmdin.getValueForTag("--block-id", "-b");

  if(kind_input.first){
    map = map = Fiff::Formatting::tagKinds();
    user_input = kind_input.second;
  } else if(type_input.first){
    map = map = Fiff::Formatting::tagTypes();
    user_input = type_input.second;
  } else if(block_input.first){
    map = map = Fiff::Formatting::blockIds();
    user_input = block_input.second;
  }

  if(Core::StringManipulation::isNumber(user_input)){
    int val = std::stoi(user_input);
    auto element = map.find(val);
    if (element != map.end()){
      std::cout << element->first << " - " << element->second << "\n";
    }
  } else {
    for (auto& element : map){
      if (element.second.find(user_input) != std::string::npos || user_input.empty()){
        std::cout << element.first << " - " << element.second << "\n";
      }
    }
  }

  return 0;
}