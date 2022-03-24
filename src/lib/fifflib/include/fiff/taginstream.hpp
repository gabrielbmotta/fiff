//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_TAGINSTREAM_HPP
#define FIFFFILEEXPLORER_TAGINSTREAM_HPP

#include <istream>

class TagInStream{
public:
  Tag readNextTag();
  Tag peekNextTag();

  void goToReadPosition(std::streampos pos);
  std::streampos currentReadPosition();

protected:
  std::istream m_istream;
};


#endif //FIFFFILEEXPLORER_TAGINSTREAM_HPP
