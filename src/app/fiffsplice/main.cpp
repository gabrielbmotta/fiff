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

  while(!rawSource.atEnd()){
    auto tag = rawSource.getTag();
    if(tag.kind == Fiff::Kind::block_start && static_cast<int32_t>(tag.data) == static_cast<int32_t>(Fiff::Block::isotrak)){
      while(!digSource.atEnd()){
        auto digFileTag = digSource.getTag();
        if(tag.kind == Fiff::Kind::block_start && static_cast<int32_t>(tag.data) == static_cast<int32_t>(Fiff::Block::isotrak)){
          output.writeTag(digFileTag);
          bool readAllDig = false;
          while(!readAllDig){
            auto dig = digSource.getTag();
            if(dig.type == Fiff::Type::dig_point_struct_ ||
                    (tag.kind == Fiff::Kind::block_end && static_cast<int32_t>(tag.data) == static_cast<int32_t>(Fiff::Block::isotrak))){
              output.writeTag(dig);
            } else{
              readAllDig = true;
            }
          }
        }
        break;
      }
      bool discardAllDig = false;
      while(!discardAllDig){
        auto dig = rawSource.getTag();
        if(dig.type == Fiff::Type::dig_point_struct_ ||
                (tag.kind == Fiff::Kind::block_end && static_cast<int32_t>(tag.data) == static_cast<int32_t>(Fiff::Block::isotrak))){
        } else{
          discardAllDig = true;
        }
      }
    } else if(tag.kind == Fiff::Kind::dig_point){
      *static_cast<int32_t*>(tag.data.byteArray) = -1;
      output.writeTag(tag);
    }else if(tag.kind == Fiff::Kind::dir){
      //do nothing.
    } else {
      output.writeTag(tag);
    }
  }



  return 0;
}
