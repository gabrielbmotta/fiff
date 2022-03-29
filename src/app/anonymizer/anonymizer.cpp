#include "anonymizer.hpp"

void Anonymizer::setInput(Fiff::Input&& input)
{
  m_input = std::move(input);
}

void Anonymizer::setOutput(Fiff::Output&& output)
{
  m_output = std::move(output);
}

void Anonymizer::anonymize()
{
  while(!m_input.atEnd()){
    auto tag = m_input.getTag();
    trackBlockTypes(tag);
    censorTag(tag);
    m_output.writeTag(tag);
  }
}

void Anonymizer::trackBlockTypes(const Fiff::Tag &tag)
{
  if(tag.kind == Fiff::Id::Kind::block_start){
    m_blockHierarchy.push(*reinterpret_cast<int32_t*>(tag.data));
  } else if (tag.kind == Fiff::Id::Kind::block_end){
    m_blockHierarchy.pop();
  }
}

void Anonymizer::censorTag(Fiff::Tag& tag){
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
      if(m_blockHierarchy.top() == Fiff::Id::Block::b_meas_info)
      {
        std::cout << "Found description: " << reinterpret_cast<char*>(tag.data) << "\n";
        delete [] reinterpret_cast<char*>(tag.data);
        tag.size = 1;
        tag.data = new char[1];

        auto* name = reinterpret_cast<char*>(tag.data);
        for(int i = 0; i < tag.size; ++i){
          name[i] = ' ';
        }
      }
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
