//
// Created by Gabriel Motta on 4/12/22.
//

#include <fiff/input.hpp>
#include <fiff/output.hpp>
#include <core/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
  Core::CommandLineInput cmdin(argc, argv);

  std::string rawFile = cmdin.getValueForTag("--raw", "-r").second;
  std::string digFile = cmdin.getValueForTag("--digitization", "-d").second;
  std::string outFile = cmdin.getValueForTag("--output", "-o").second;

  auto rawSource = Fiff::Input::fromFile(rawFile);
  auto digSource = Fiff::Input::fromFile(digFile);
  auto output = Fiff::Output::toFile(outFile);

  std::cout << " > Reading from raw file...\n";
  while(!rawSource.atEnd()){
    auto tag = rawSource.getTag();
    if(tag.kind == Fiff::Kind::block_start && static_cast<int32_t>(tag.data) == static_cast<int32_t>(Fiff::Block::isotrak)){
      std::cout << " > Raw file digitization data reached. Switching to digitizer file.\n";
      std::cout << " > Reading from digitizer file...\n";
      while(!digSource.atEnd()){
        auto digFileTag = digSource.getTag();
        if(digFileTag.kind == Fiff::Kind::block_start && static_cast<int32_t>(digFileTag.data) == static_cast<int32_t>(Fiff::Block::isotrak)){
          std::cout << " > Digitizer data found in digitizer file. Splicing...\n";
          output.writeTag(digFileTag);
          bool readAllDig = false;
          while(!readAllDig){
            auto dig = digSource.getTag();
            if((dig.kind == Fiff::Kind::block_end && static_cast<int32_t>(dig.data) == static_cast<int32_t>(Fiff::Block::isotrak))){
              output.writeTag(dig);
              std::cout << " > All digitizer data spliced.\n";
              readAllDig = true;
            } else{
              output.writeTag(dig);
            }
          }
        }
        break;
      }
      bool discardAllDig = false;
      while(!discardAllDig){
        std::cout << " > Skipping digitization data from raw file...\n";
        auto dig = rawSource.getTag();
        if(dig.type == Fiff::Type::dig_point_struct_ ||
                (tag.kind == Fiff::Kind::block_end && static_cast<int32_t>(tag.data) == static_cast<int32_t>(Fiff::Block::isotrak))){
        } else{
          std::cout << " > Raw file digitization skipped.\n";
          std::cout << " > Continuing raw file parsing...\n";
          discardAllDig = true;
        }
      }
    } else if(tag.kind == Fiff::Kind::dir_pointer){
      std::cout << " > Cleared directory pointer.\n";
      *static_cast<int32_t*>(tag.data.byteArray) = -1;
      output.writeTag(tag);
    }else if(tag.kind == Fiff::Kind::dir){
      std::cout << " > Skipped directory.\n";
      //do nothing.
    } else {
      output.writeTag(tag);
    }
  }



  return 0;
}
