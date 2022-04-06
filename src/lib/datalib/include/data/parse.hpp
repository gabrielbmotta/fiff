//
// Created by Gabriel Motta on 4/6/22.
//

#ifndef FIFFFILEEXPLORER_PARSE_HPP
#define FIFFFILEEXPLORER_PARSE_HPP

#endif //FIFFFILEEXPLORER_PARSE_HPP

#include <map>
#include <any>
#include <string>

namespace Data{
std::map<std::string, std::any> parse(const std::string& filePath);
}
