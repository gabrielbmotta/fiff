//
// Created by Gabriel Motta on 5/2/22.
//

#include "core/commandlineinput.hpp"
#include "fiff/input.hpp"
#include "core/stringmanip.hpp"
#include "fiff/data.hpp"
#include "fiff/types.hpp"

#include <string>
#include <sstream>
#include <iostream>
#include <vector>
#include <list>

struct DataMatrix{
  float* data;
  int numChannels;
  int numSamples;
};

std::vector<Fiff::DigitizerPoint> getDigitizerPoints(const std::string& filePath);
DataMatrix getRawData(const std::string& filePath);

int main (int argc, char* argv[])
{
  Core::CommandLineInput cmdin(argc, argv);

  std::string rawFilePath = cmdin.getValueForTag("--raw-file", "-r").second;
  std::string digFilePath = cmdin.getValueForTag("--dig-file", "-d").second;
  std::string hpiCoils = cmdin.getValueForTag("--hpi-coils", "-c").second;

  std::vector<int> coilFreqs{};
  std::stringstream coilInput(hpiCoils);

  if(rawFilePath.empty()){
    std::cerr << "No raw file provided.\n";
    return 1;
  }

  if(digFilePath.empty()){
    std::cout << "No digitizer file provided. Will use raw file as digitizer source.\n";
    digFilePath = rawFilePath;
  }

  while(coilInput.good()){
    std::string coil;
    getline(coilInput, coil, ',');
    if(Core::StringManipulation::isNumber(coil)){
      coilFreqs.push_back(std::stoi(coil));
    } else {
      std::cerr << "Coil frequency provided is not a number.\n";
      return 1;
    }
  }

  std::vector<Fiff::DigitizerPoint> digitizerPoints = getDigitizerPoints(digFilePath);

  std::vector<Fiff::DigitizerPoint> hpiPoints;
  for(auto &point: digitizerPoints)
  {
    if(point.kind == Fiff::PointDefinition::hpi)
    {
      hpiPoints.push_back(point);
    }
  }



}

std::vector<Fiff::DigitizerPoint> getDigitizerPoints(const std::string& filePath)
{
  auto digFile = Fiff::Input::fromFile(filePath);
  std::vector<Fiff::DigitizerPoint> digitizerPoints;

  while(!digFile.atEnd())
  {
    auto tag = digFile.getTag();
    if(tag.kind == Fiff::Kind::dig_point)
    {
      digitizerPoints.emplace_back(Fiff::DigitizerPoint(tag.data));
    }
  }

  return digitizerPoints;
}

DataMatrix getRawData(const std::string& filePath)
{
  auto rawFile = Fiff::Input::fromFile(filePath);

  DataMatrix data{};

  bool rawDataFound = false;
  std::vector<Fiff::ChannelInfo> chanInfo;
  while(!rawFile.atEnd())
  {
    auto tag = rawFile.getTag();

    if(tag.kind == Fiff::Kind::nchan){
      data.numChannels = static_cast<int32_t>(tag.data);
      chanInfo.reserve(data.numChannels);
      continue;
    }
    if(tag.kind == Fiff::Kind::ch_info){
      chanInfo.push_back(static_cast<Fiff::ChannelInfo>(tag.data));
      continue;
    }
    if(tag.kind == Fiff::Kind::block_start && static_cast<int32_t>(tag.data) == Fiff::Block::raw_data){
      rawDataFound = true;
      break;
    }
  }

  if (data.numChannels != static_cast<int32_t>(chanInfo.size())){
    std::cerr << "Number of channels mismatch.\n";
    return {};
  }

  if(!rawDataFound || !data.numChannels){
    std::cerr << "Missing data.\n";
    return {};
  }

  std::list<Fiff::Tag> dataTags;
  while(!rawFile.atEnd()){
    auto tag = rawFile.getTag();
    if(tag.kind == Fiff::Kind::block_end && static_cast<int32_t>(tag.data) == Fiff::Block::raw_data){
      break;
    }
    if(tag.kind == Fiff::Kind::data_buffer)
    dataTags.emplace_back(tag);
  }

  int numSamples = 0;
  for(auto& datatag : dataTags){
    numSamples += datatag.size;
  }

  int dataSize = 0;
  switch(dataTags.front().type)
  {
    case Fiff::Type::float_:
    case Fiff::Type::int32_:
      dataSize = 4;
      break;
    case Fiff::Type::dau_pack16_:
      dataSize = 2;
      break;
    case Fiff::Type::double_:
      dataSize = 8;
      break;
    default:
      std::cerr << "Data type not accounted for. Defaulting to size 4.\n";
      dataSize = 4;
      break;
  }
  data.numSamples = (numSamples) / (dataSize * data.numChannels);
  data.data = new float[data.numChannels * data.numSamples];

  std::cout << "Num Channels: " << data.numChannels << "\n";
  std::cout << "Num Samples:" << data.numSamples << "\n";

  return {};
}



