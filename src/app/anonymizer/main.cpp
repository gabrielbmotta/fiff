#include <fiff/input.hpp>
#include <fiff/output.hpp>
#include <fiff/datatypes.hpp>
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
    //all these 'kinds' of tags contain a fileID struct, which contains info related to
    //measurement date
    case Fiff::Id::Kind::file_id:
    case Fiff::Id::Kind::block_id:
    case Fiff::Id::Kind::parent_file_id:
    case Fiff::Id::Kind::parent_block_id:
    case Fiff::Id::Kind::ref_file_id:
    case Fiff::Id::Kind::ref_block_id:
    {
      FIFFLIB::FiffId inId = tag.toFiffID();
      QDateTime inMeasDate = QDateTime::fromSecsSinceEpoch(inId.time.secs, Qt::LocalTime);
      emit readingIdMeasurementDate(inMeasDate);

      QDateTime outMeasDate;

      if(m_bUseMeasurementDateOffset)
      {
        outMeasDate = inMeasDate.addDays(-m_iMeasurementDateOffset);
      } else {
        outMeasDate = m_dMeasurementDate;
      }

      FIFFLIB::FiffId outId(inId);
      outId.machid[0] = m_BDfltMAC[0];
      outId.machid[1] = m_BDfltMAC[1];
      outId.time.secs = static_cast<int32_t>(outMeasDate.toSecsSinceEpoch());
      outId.time.usecs = 0;

      const int fiffIdSize(sizeof(inId)/sizeof(FIFFLIB::fiff_int_t));
      FIFFLIB::fiff_int_t outData[fiffIdSize];
      outData[0] = outId.version;
      outData[1] = outId.machid[0];
      outData[2] = outId.machid[1];
      outData[3] = outId.time.secs;
      outData[4] = outId.time.usecs;

      tag.resize(fiffIdSize*sizeof(FIFFLIB::fiff_int_t));
      memcpy(tag.data(),reinterpret_cast<char*>(outData),fiffIdSize*sizeof(FIFFLIB::fiff_int_t));
      printIfVerbose("MAC address in ID tag changed: " + inId.toMachidString() + " -> "  + outId.toMachidString());
      printIfVerbose("Measurement date in ID tag changed: " + inMeasDate.toString("dd.MM.yyyy hh:mm:ss.zzz t") + " -> " + outMeasDate.toString("dd.MM.yyyy hh:mm:ss.zzz t"));
      break;
    }
    case Fiff::Id::Kind::meas_date:
    {
      QDateTime inMeasDate(QDateTime::fromSecsSinceEpoch(*tag.toInt(), Qt::LocalTime));
      emit readingFileMeasurementDate(inMeasDate);
      QDateTime outMeasDate;

      if(m_bUseMeasurementDateOffset)
      {
        outMeasDate = inMeasDate.addDays(-m_iMeasurementDateOffset);
      } else {
        outMeasDate = m_dMeasurementDate;
      }

      FIFFLIB::fiff_int_t outData[1];
      outData[0] = static_cast<int32_t>(outMeasDate.toSecsSinceEpoch());
      memcpy(tag.data(),reinterpret_cast<char*>(outData),sizeof(FIFFLIB::fiff_int_t));
      printIfVerbose("Measurement date changed: " + inMeasDate.toString("dd.MM.yyyy hh:mm:ss.zzz t") + " -> " + outMeasDate.toString("dd.MM.yyyy hh:mm:ss.zzz t"));
      break;
    }
    case Fiff::Id::Kind::description:
    {
      QString inStr(tag.data());
      emit readingFileComment(inStr);

      if(m_pBlockTypeList->top() == FIFFB_MEAS_INFO)
      {
        QString outStr(m_sDefaultString);
        tag.resize(outStr.size());
        memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
        printIfVerbose("Description of the measurement block changed: " + inStr + " -> " + outStr);
      }
      break;
    }
    case Fiff::Id::Kind::experimenter:
    {
      QString inStr(tag.data());
      emit readingFileExperimenter(inStr);

      QString outStr(m_sDefaultString);
      tag.resize(outStr.size());
      memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
      printIfVerbose("Experimenter changed: " + inStr + " -> " + outStr);
      break;
    }
    case Fiff::Id::Kind::subj_id:
    {
      qint32 inSubjID(*tag.toInt());
      emit readingSubjectId(inSubjID);
      qint32 outSubjID(m_iSubjectId);
      memcpy(tag.data(),&outSubjID, sizeof(qint32));
      printIfVerbose("Subject ID changed: " + QString::number(inSubjID) + " -> " + QString::number(outSubjID));
      break;
    }
    case Fiff::Id::Kind::subj_first_name:
    {
      QString inFirstName(tag.data());
      emit readingSubjectFirstName(inFirstName);
      QString outFirstName(m_sSubjectFirstName);
      tag.resize(outFirstName.size());
      memcpy(tag.data(),outFirstName.toUtf8(),static_cast<size_t>(outFirstName.size()));
      printIfVerbose("Subject first name changed: " + inFirstName + " -> " + outFirstName);
      break;
    }
    case Fiff::Id::Kind::subj_middle_name:
    {
      QString inStr(tag.data());
      emit readingSubjectMiddleName(inStr);
      QString outStr(m_sSubjectMidName);
      tag.resize(outStr.size());
      memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
      printIfVerbose("Subject middle name changed: " + inStr + " -> " + outStr);
      break;
    }
    case Fiff::Id::Kind::subj_last_name:
    {
      QString inStr(tag.data());
      emit readingSubjectLastName(inStr);
      QString outStr(m_sSubjectLastName);
      tag.resize(outStr.size());
      memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
      printIfVerbose("Subject last name changed: " + inStr + " -> " + outStr);
      break;
    }
    case Fiff::Id::Kind::subj_birth_day:
    {
      QDate inBirthday(QDate::fromJulianDay(*tag.toJulian()));
      emit readingSubjectBirthday(inBirthday);
      QDate outBirthday;

      if(m_bUseSubjectBirthdayOffset)
      {
        outBirthday = inBirthday.addDays(-m_iSubjectBirthdayOffset);
      } else {
        outBirthday = m_dSubjectBirthday;
      }

      FIFFLIB::fiff_int_t outData[1];
      outData[0] = static_cast<int32_t> (outBirthday.toJulianDay());
      memcpy(tag.data(),reinterpret_cast<char*>(outData),sizeof(FIFFLIB::fiff_int_t));
      printIfVerbose("Subject birthday date changed: " + inBirthday.toString("dd.MM.yyyy") + " -> " + outBirthday.toString("dd.MM.yyyy"));
      break;
    }
    case Fiff::Id::Kind::subj_sex:
    {
      qint32 inSubjectSex(*tag.toInt());
      emit readingSubjectSex(inSubjectSex);
      if(m_bBruteMode)
      {
        qint32 outSubjSex(m_iSubjectSex);
        memcpy(tag.data(),&outSubjSex, sizeof(qint32));
        printIfVerbose("Subject sex changed: " + subjectSexToString(inSubjectSex) + " -> " + subjectSexToString(outSubjSex));
      }
      break;
    }
    case Fiff::Id::Kind::subj_hand:
    {
      qint32 inSubjectHand(*tag.toInt());
      emit readingSubjectHand(inSubjectHand);
      if(m_bBruteMode)
      {
        qint32 newSubjHand(m_iSubjectHand);
        memcpy(tag.data(),&newSubjHand, sizeof(qint32));
        printIfVerbose("Subject handedness changed: " + subjectHandToString(inSubjectHand) + " -> " + subjectHandToString(newSubjHand));
      }
      break;
    }
    case Fiff::Id::Kind::subj_weight:
    {
      float inWeight(*tag.toFloat());
      emit readingSubjectWeight(inWeight);
      if(m_bBruteMode)
      {
        float outWeight(m_fSubjectWeight);
        memcpy(tag.data(),&outWeight,sizeof(float));
        printIfVerbose("Subject weight changed: " + QString::number(static_cast<double>(inWeight)) + " -> " + QString::number(static_cast<double>(outWeight)));
      }
      break;
    }
    case Fiff::Id::Kind::subj_height:
    {
      float inHeight(*tag.toFloat());
      emit readingSubjectHeight(inHeight);
      if(m_bBruteMode)
      {
        float outHeight(m_fSubjectHeight);
        memcpy(tag.data(),&outHeight,sizeof(float));
        printIfVerbose("Subject height changed: " + QString::number(static_cast<double>(inHeight)) + " -> " + QString::number(static_cast<double>(outHeight)));
      }
      break;
    }
    case Fiff::Id::Kind::subj_comment:
    {
      QString inStr(tag.data());
      emit readingSubjectComment(inStr);
      QString outStr(m_sSubjectComment);
      tag.resize(outStr.size());
      memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
      printIfVerbose("Subject comment changed: " + inStr + " -> " + outStr);
      break;
    }
    case Fiff::Id::Kind::subj_his_id:
    {
      QString inSubjectHisId(tag.data());
      emit readingSubjectHisId(inSubjectHisId);
      QString outSubjectHisId(m_sSubjectHisId);
      tag.resize(outSubjectHisId.size());
      memcpy(tag.data(),outSubjectHisId.toUtf8(),static_cast<size_t>(outSubjectHisId.size()));
      printIfVerbose("Subject Hospital-ID(His Id) changed: " + inSubjectHisId + " -> " + outSubjectHisId);
      break;
    }
    case Fiff::Id::Kind::proj_id:
    {
      qint32 inProjID(*tag.toInt());
      emit readingProjectId(inProjID);
      if(m_bBruteMode)
      {
        qint32 newProjID(m_iProjectId);
        memcpy(tag.data(),&newProjID,sizeof(qint32));
        printIfVerbose("ProjectID changed: " + QString::number(inProjID) + " -> " + QString::number(newProjID));
      }
      break;
    }
    case Fiff::Id::Kind::proj_name:
    {
      QString inStr(tag.data());
      emit readingProjectName(inStr);
      if(m_bBruteMode)
      {
        QString outStr(m_sProjectName);
        tag.resize(outStr.size());
        memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
        printIfVerbose("Project name changed: " + inStr + " -> " + outStr);
      }
      break;
    }
    case Fiff::Id::Kind::proj_aim:
    {
      QString inStr(tag.data());
      emit readingProjectAim(inStr);
      if(m_bBruteMode)
      {
        QString outStr(m_sProjectAim);
        tag.resize(outStr.size());
        memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
        printIfVerbose("Project aim changed: " + inStr + " -> " + outStr);
      }
      break;
    }
    case Fiff::Id::Kind::proj_persons:
    {
      QString inStr(tag.data());
      emit readingProjectPersons(inStr);
      QString outStr(m_sProjectPersons);
      tag.resize(outStr.size());
      memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
      printIfVerbose("Project persons changed: " + inStr + " -> " + outStr);
      break;
    }
    case Fiff::Id::Kind::proj_comment:
    {
      QString inStr(tag.data());
      emit readingProjectComment(inStr);
      if(m_bBruteMode)
      {
        QString outStr(m_sProjectComment);
        tag.resize(outStr.size());
        memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
        printIfVerbose("Project comment changed: " + inStr + " -> " + outStr);
      }
      break;
    }
    case Fiff::Id::Kind::mri_pixel_data:
    {
      printIfVerbose("  ");
      printIfVerbose("Warning: The input fif file contains MRI data.");
      printIfVerbose("Warning: Beware that a subject''s face can be reconstructed from it");
      printIfVerbose("Warning: This software can not anonymize MRI data, at the moment.");
      printIfVerbose("  ");
      emit mriDataFoundInFile(true);
      break;
    }
    case Fiff::Id::Kind::mne_env_working_dir:
    {
      QString inStr(tag.data());
      emit readingMNEWorkingDir(inStr);
      if(m_bMNEEnvironmentMode || m_bBruteMode)
      {
        QString outStr(m_sMNEWorkingDir);
        tag.resize(outStr.size());
        memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
        printIfVerbose("MNE working directory info changed: " + inStr + " -> " + outStr);
      }
      break;
    }
    case Fiff::Id::Kind::mne_env_command_line:
    {
      QString inStr(tag.data());
      emit readingMNECommandLine(inStr);
      if(m_bMNEEnvironmentMode || m_bBruteMode)
      {
        QString outStr(m_sMNECommand);
        tag.resize(outStr.size());
        memcpy(tag.data(),outStr.toUtf8(),static_cast<size_t>(outStr.size()));
        printIfVerbose("MNE command line info changed: " + inStr + " -> " + outStr);
      }
      break;
    }
    default:
    {
    }//default
  }//switch
}
