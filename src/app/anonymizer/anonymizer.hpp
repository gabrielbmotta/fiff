#ifndef FIFFFILEEXPLORER_ANONYMIZER_HPP
#define FIFFFILEEXPLORER_ANONYMIZER_HPP

#include <fiff/input.hpp>
#include <fiff/output.hpp>
#include <fiff/datatypes.hpp>

#include <string>
#include <stack>

class Anonymizer {
public:
  void setInput(Fiff::Input&& input);
  void setOutput(Fiff::Output&& output);

  void anonymize();

private:
  void trackBlockTypes(const Fiff::Tag& tag);
  void censorTag(Fiff::Tag& tag);

  Fiff::Input m_input;
  Fiff::Output m_output;
  std::stack<int> m_blockHierarchy;
};

#endif //FIFFFILEEXPLORER_ANONYMIZER_HPP