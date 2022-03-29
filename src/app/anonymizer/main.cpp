#include "anonymizer.hpp"

#include <core/commandlineinput.hpp>

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
  anonymizer.setInput(Fiff::Input::fromFile(inputPath));
  anonymizer.setOutput(Fiff::Output::toFile(outputPath));

  anonymizer.anonymize();

  return 0;
}
