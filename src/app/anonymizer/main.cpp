#include "anonymizer.hpp"

#include <utils/commandlineinput.hpp>

#include <iostream>
#include <string>


int main(int argc, char* argv[])
{
  Core::CommandLineInput cmdin(argc, argv);

  if(cmdin.tagExists("--help","-h")){
    std::cout << "|---      anonymizer      ---|\n\n"
              << "Usage: anonymizer -i /path/to/file -o /another/path\n\n"
              << "-i --input <input>\t Path to input file.\n\n"
              << "-o --output <output>\t Path to output file.\n";
  }

  std::string inputPath = cmdin.getValueForTag("--input", "-i").second;
  std::string outputPath = cmdin.getValueForTag("--output", "-o").second;

  if(inputPath.empty()){
    std::cout << "No input file provided.\n";
    return 1;
  }
  if(outputPath.empty()){
    //TODO: establish sensible default output
    std::cout << "No output file provided.\n";
  }

  Anonymizer anonymizer;
  auto input = Fiff::Input::fromFile(inputPath);
  auto output = Fiff::Output::toFile(outputPath, input.getEndianess());

  anonymizer.setInput(&input);
  anonymizer.setOutput(&output);

  anonymizer.anonymize();

  return 0;
}
