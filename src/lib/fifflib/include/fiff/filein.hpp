//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_FILEIN_HPP
#define FIFFFILEEXPLORER_FILEIN_HPP

#include "fiff/taginstream.hp"
#include <fstream>

class FileIn : TagInStream{
public:
  FileIn() = default;
  FileIn(const std::string& filePath);

  void open(const std::string &filePath);
  void open();
  bool isOpen();
};


#endif //FIFFFILEEXPLORER_FILEIN_HPP
