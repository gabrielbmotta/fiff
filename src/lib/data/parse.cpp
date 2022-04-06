//
// Created by Gabriel Motta on 4/6/22.
//

#include "data/parse.hpp"
#include "core/stringmanip.hpp"
#include "fiff/input.hpp"

static std::map<std::string, std::any> parseFif(const std::string& filePath);

std::map<std::string, std::any> Data::parse(const std::string& filePath)
{
  if(Core::StringManipulation::endsWith(filePath, ".fif")){
    return parseFif(filePath);
  }
  return {};
}

std::map<std::string, std::any> parseFif(const std::string& filePath)
{
  auto myFile = Fiff::Input::fromFile(filePath);
  std::map<std::string, std::any> returnMap;

//  while(!myFile.atEnd()){
//    auto tag = myFile.getTag();
//    if()
//  }

  return {};
}
