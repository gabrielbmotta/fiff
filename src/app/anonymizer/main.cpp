#include <fiff/input.hpp>
#include <fiff/output.hpp>
#include <fiff/datatypes.hpp>
#include <fiff/formatting.hpp>
#include <core/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include <iostream>
#include <string>

void censorTag(Fiff::Tag& tag);

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

  auto inFile = Fiff::Input::fromFile(inputPath);
  auto outFile = Fiff::Output::toFile(outputPath);

  while(!inFile.atEnd()){
    auto tag = inFile.getTag();
    censorTag(tag);
    outFile.writeTag(tag);
  }

  return 0;
}

void censorTag(Fiff::Tag& tag){
  switch (tag.kind)
  {
    case Fiff::Id::Kind::file_id:
    case Fiff::Id::Kind::block_id:
    case Fiff::Id::Kind::parent_file_id:
    case Fiff::Id::Kind::parent_block_id:
    case Fiff::Id::Kind::ref_file_id:
    case Fiff::Id::Kind::ref_block_id:
    {
      auto* id = reinterpret_cast<Fiff::Type::id_t*>(tag.data);

      id->machid[0] = 0;
      id->machid[1] = 0;
      id->time_sec = 0;
      id->time_usec = 0;

      break;
    }
    case Fiff::Id::Kind::meas_date:
    {
      auto* date = reinterpret_cast<int32_t*>(tag.data);
      *date = 0;
      break;
    }
    case Fiff::Id::Kind::description:
    {
//      QString inStr(tag.data());
//      emit readingFileComment(inStr);
//
//      if(m_pBlockTypeList->top() == FIFFB_MEAS_INFO)
//      {
//        QString outStr(m_sDefaultString);
//        tag.resize(outStr.size());
//        memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
//        printIfVerbose("Description of the measurement block changed: " + inStr + " -> " + outStr);
//      }
      break;
    }
    case Fiff::Id::Kind::experimenter:
    {
      std::cout << "Found experimenter: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];

      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::subj_id:
    {
      auto* id = reinterpret_cast<int*>(tag.data);
      *id = 0;
      break;
    }
    case Fiff::Id::Kind::subj_first_name:
    {
      std::cout << "Found subj first name: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::subj_middle_name:
    {
      std::cout << "Found subj middle name: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::subj_last_name:
    {
      std::cout << "Found subj last name: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::subj_birth_day:
    {
      auto* julian = reinterpret_cast<int*>(tag.data);
      *julian = 0;
      break;
    }
    case Fiff::Id::Kind::subj_sex:
    {
      auto* sex = reinterpret_cast<int*>(tag.data);
      *sex = 0;
      break;
    }
    case Fiff::Id::Kind::subj_hand:
    {
      break;
    }
    case Fiff::Id::Kind::subj_weight:
    {
      auto* weight = reinterpret_cast<int*>(tag.data);
      *weight = 0;
      break;
    }
    case Fiff::Id::Kind::subj_height:
    {
      auto* height = reinterpret_cast<int*>(tag.data);
      *height = 0;
      break;
    }
    case Fiff::Id::Kind::subj_comment:
    {
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::subj_his_id:
    {
      std::cout << "Found subj his id: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::proj_id:
    {
      auto* id = reinterpret_cast<int*>(tag.data);
      *id = 0;
      break;
    }
    case Fiff::Id::Kind::proj_name:
    {
      std::cout << "Found proj name: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::proj_aim:
    {
      std::cout << "Found proj aim: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::proj_persons:
    {
      std::cout << "Found proj persons: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::proj_comment:
    {
      std::cout << "Found proj comments: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::mri_pixel_data:
    {
      std::cerr << "Cannot anonymize MRI Data. Resulting file in NOT anonymous.";
      break;
    }
    case Fiff::Id::Kind::mne_env_working_dir:
    {
      std::cout << "Found mne working dir: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    case Fiff::Id::Kind::mne_env_command_line:
    {
      std::cout << "Found mne cmd line: " << reinterpret_cast<char*>(tag.data) << "\n";
      delete [] reinterpret_cast<char*>(tag.data);
      tag.size = 1;
      tag.data = new char[1];
      auto* name = reinterpret_cast<char*>(tag.data);
      for(int i = 0; i < tag.size; ++i){
        name[i] = ' ';
      }
      break;
    }
    default:
    {
    }//default
  }//switch
}
