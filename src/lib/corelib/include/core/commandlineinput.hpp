//
// Created by Gabriel Motta on 3/7/22.
//

#ifndef FIFFFILEEXPLORER_COMMANDLINEINPUT_HPP
#define FIFFFILEEXPLORER_COMMANDLINEINPUT_HPP

#include <string>
#include <vector>

namespace Core {
class CommandLineInput {
public:
  CommandLineInput(int &argc, char *argv[]);
  std::string getValueForTag(const std::string &option) const;
  bool charTagExists(const std::string &option) const;
  bool stringTagExists(const std::string &option) const;

private:
  std::vector <std::string> args;
};
}
#endif //FIFFFILEEXPLORER_COMMANDLINEINPUT_HPP
