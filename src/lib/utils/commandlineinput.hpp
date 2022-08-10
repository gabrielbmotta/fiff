//
// Created by Gabriel Motta on 3/7/22.
//

#ifndef FIFF_LIBUTILS_COMMANDLINEINPUT_HPP
#define FIFF_LIBUTILS_COMMANDLINEINPUT_HPP

#include <string>
#include <vector>

namespace Core {
class CommandLineInput {
public:
  CommandLineInput(int &argc, char *argv[]);
  std::pair<bool, std::string> getValueForTag(const std::string &option, const std::string &shortoption = "") const;
  std::string getValueThatEndsWith(const std::string& substr);
  bool tagExists(const std::string &option, const std::string &shortoption = "") const;

private:
  std::vector <std::string> args;
};
}
#endif //FIFF_LIBUTILS_COMMANDLINEINPUT_HPP
