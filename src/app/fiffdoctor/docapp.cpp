#include "docapp.hpp"
#include "color.h"
#include "fiffsource.hpp"

#include <core/stringmanip.hpp>
#include <fiff/json.hpp>

#include <string>

DocApp::DocApp() {
  _commandFnMap = {{"list", &DocApp::list},      {"load", &DocApp::load},
                   {"show", &DocApp::show},      {"edit", &DocApp::edit},
                   {"create", &DocApp::create},  {"copy", &DocApp::copy},
                   {"remove", &DocApp::remove},  {"close", &DocApp::close},
                   {"exit", &DocApp::exit},      {"quit", &DocApp::exit},
                   {"json", &DocApp::exportJSON}};
}

void DocApp::run() {
  _running = true;
  while (_running) {
    std::cout << COLOR_GREEN << "<<< " << COLOR_DEFAULT;
    std::string userInput;
    std::getline(std::cin, userInput);
    processUserInput(userInput);
  }
}

void DocApp::processUserInput(const std::string &input) {
  auto cmdEndIndex = input.find(' ');
  std::string command = input.substr(0, cmdEndIndex);

  if (_commandFnMap.find(command) != _commandFnMap.end()) {
    auto commandFn = _commandFnMap.at(command);
    (this->*(commandFn))(input.substr(cmdEndIndex + 1));
  }
}

void DocApp::load(const std::string &command) {
  std::cout << "Loading from file: " << command << "\n";

  auto inFile = Fiff::Input::fromFile(command);

  FiffSource *source = new FiffSource;
  while (!inFile.atEnd()) {
    tag_node node;
    node.tag = new Fiff::Tag(inFile.getTag());
    source->tags.push_back(node);
  }

  source->name = command;
  source->path = command;
  source->endianness = inFile.getEndianess();
  source->indexNodes();

  fiff_sources.push_back(source);
}

void DocApp::show(const std::string &command) {
  (void)command;
  auto index = command.find(' ');
  std::string cmd = command.substr(0, index);
  std::string rest = command.substr(index + 1);

  unsigned int detail = INT_MAX;
  std::vector<int> match;

  if (cmd == "detail" && Core::StringManipulation::isNumber(rest)) {
    detail = std::stoi(rest);
  } else if (cmd == "match") {
    auto vec = Core::StringManipulation::getVectorFrom<int>(rest, '.');
    for (auto &element : vec) {
      match.push_back(element);
    }
  }

  if (cmd == "blocks") {
    for (auto &source : fiff_sources) {
      source->printBlocks();
    }
  } else {
    for (auto &source : fiff_sources) {
      source->printTags(detail, match);
    }
  }
}

void DocApp::list(const std::string &command) {
  (void)command;
  auto size = fiff_sources.size();
  std::cout << "You have " << size;

  if (size == 1)
    std::cout << " file";
  else
    std::cout << " files";

  std::cout << " open.\n";

  if (size) {
    std::cout << "\n----------\n";
    for (auto *element : fiff_sources) {
      std::cout << *element << "\n----------\n";
    }
  }
}

void DocApp::edit(const std::string &command) { (void)command; }

void DocApp::create(const std::string &command) { (void)command; }

void DocApp::copy(const std::string &command) { (void)command; }

void DocApp::remove(const std::string &command) { (void)command; }

void DocApp::close(const std::string &command) { (void)command; }

void DocApp::exit(const std::string &command) {
  (void)command;
  _running = false;
}

void DocApp::exportJSON(const std::string &command) {
  Fiff::fiffToJson(command.c_str(), "json_test.json");
}
