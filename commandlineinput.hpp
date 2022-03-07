//
// Created by Gabriel Motta on 3/7/22.
//

#ifndef FIFFFILEEXPLORER_COMMANDLINEINPUT_HPP
#define FIFFFILEEXPLORER_COMMANDLINEINPUT_HPP

class CommandLineInput{
public:
  CommandLineInput (int &argc, char *argv[]){
    for (int i = 1; i < argc; ++i)
      this->args.push_back(std::string(argv[i]));
  }

  std::string getValueForTag(const std::string &option) const{
    auto itr = std::find(this->args.begin(), this->args.end(), option);
    if (itr != this->args.end() && ++itr != this->args.end()){
      return *itr;
    }
    return std::string;
  }

  bool charTagExists(const std::string &option) const{
    return std::find(this->args.begin(), this->args.end(), option) != this->args.end();
  }

  bool stringTagExists(const std::string &option) const {
    return std::find(this->args.begin(), this->args.end(), option) != this->args.end();
  }
private:
  std::vector <std::string> args;
};

#endif //FIFFFILEEXPLORER_COMMANDLINEINPUT_HPP
