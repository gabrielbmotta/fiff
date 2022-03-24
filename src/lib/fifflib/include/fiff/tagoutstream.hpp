//
// Created by Gabriel Motta on 3/24/22.
//

#ifndef FIFFFILEEXPLORER_TAGOUTSTREAM_HPP
#define FIFFFILEEXPLORER_TAGOUTSTREAM_HPP


class TagOutStream {
public:
  void writeTag(const Tag& tag);

  void goToWritePosition(std::streampos pos);
  std::streampos currentWritePosition();

protected:
  std::ostream m_ostream;
};


#endif //FIFFFILEEXPLORER_TAGOUTSTREAM_HPP
