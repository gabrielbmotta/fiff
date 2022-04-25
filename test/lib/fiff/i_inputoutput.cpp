//
// Created by Gabriel Motta on 4/13/22.
//

#include "catch.hpp"

#include "../../../src/lib/fiff/input.hpp"
#include "../../../src/lib/fiff/output.hpp"

const static char* testFile = "sample_audvis_trunc_raw.fif";

TEST_CASE("Data Integrity", "[input output]"){
  std::string copyFile = "sample_copy_output.fif";
  {
    auto inFile = Fiff::Input::fromFile(testFile);
    auto outFile = Fiff::Output::toFile(copyFile);
    outFile.setEndianess(inFile.getEndianess());

    while(!inFile.atEnd())
    {
      outFile.writeTag(inFile.getTag());
    }
  }

  std::ifstream original(testFile, std::ios::binary);
  std::ifstream copy(copyFile, std::ios::binary);
  char originalbuffer, copybuffer;

  bool filesAreEqual = true;
  while(!original.eof() || !copy.eof()){
    original.read(&originalbuffer, sizeof originalbuffer);
    copy.read(&copybuffer, sizeof copybuffer);

    if(originalbuffer != copybuffer){
      filesAreEqual = false;
      break;
    }
  }

  REQUIRE(filesAreEqual);
}
