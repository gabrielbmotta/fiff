//
// Created by Gabriel Motta on 3/10/22.
//

#include <string>
#include <iostream>
#include <sstream>
#include <vector>

#ifndef FIFFFILEEXPLORER_STRINGMANIP_HPP
#define FIFFFILEEXPLORER_STRINGMANIP_HPP
namespace Core {
class StringManipulation {
public:
  template<typename T>
  static std::vector<T> getVectorFrom(const std::string &item, char separator)
  {
    std::vector<T> tag_set;
    std::stringstream ss(item);

    for (T i; ss >> i;) {
      tag_set.push_back(i);
      if (ss.peek() == separator)
        ss.ignore();
    }
    return tag_set;
  }

  static bool isNumber(const std::string& s);
};
}


#endif //FIFFFILEEXPLORER_STRINGMANIP_HPP
