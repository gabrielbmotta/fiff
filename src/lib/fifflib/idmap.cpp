//
// Created by Gabriel Motta on 3/7/22.
//

#include "fiff/idmap.hpp"

std::map<int,std::string> Fiff::Formatting::_tagKind
        {{100, "(100)FIFF_FILE_ID"},
         {101, "(101)FIFF_DIR_POINTER"},
         {102, "(102)FIFF_DIR"},
         {103, "(103)FIFF_BLOCK_ID"},
         {104, "(104)FIFF_BLOCK_START"},
         {105, "(105)FIFF_BLOCK_END"},
         {200, "(200)FIFF_NCHAN"},
         {201, "(201)FIFF_SFREQ"},
         {202, "(202)FIFF_DATA_PACK"},
         {203, "(203)FIFF_CH_INFO"},
         {204, "(204)FIFF_MEAS_DATE"},
         {205, "(205)FIFF_SUBJECT"},
         {206, "(206)FIFF_COMMENT"},
         {207, "(207)FIFF_NAVE"},
         {208, "(208)FIFF_FIRST_SAMPLE"},
         {209, "(209)FIFF_LAST_SAMPLE"},
         {210, "(210)FIFF_ASPECT_KIND"},
         {211, "(211)FIFF_REF_EVENT"},
         {212, "(212)FIFF_EXPERIMENTER"},
         {213, "(213)FIFF_DIG_POINT"},
         {214, "(214)FIFF_CH_POS_VEC"},
         {215, "(215)FIFF_HPI_SLOPES"},
         {216, "(216)FIFF_HPI_NCOIL"},
         {217, "(217)FIFF_REQ_EVENT"},
         {218, "(218)FIFF_REQ_LIMIT"},
         {219, "(219)FIFF_LOWPASS"},
         {220, "(220)FIFF_BAD_CHS"},
         {221, "(221)FIFF_ARTEF_REMOVAL"},
         {222, "(222)FIFF_COORD_TRANS"},
         {223, "(223)FIFF_HIGHPASS"},
         {224, "(224)FIFF_CH_CALS_VEC"},
         {225, "(225)FIFF_HPI_BAD_CHS"},
         {226, "(226)FIFF_HPI_CORR_COEFF"},
         {227, "(227)FIFF_EVENT_COMMENT"},
         {228, "(228)FIFF_NO_SAMPLES"},
         {229, "(229)FIFF_FIRST_TIME"},
         {230, "(230)FIFF_SUBAVE_SIZE"},
         {231, "(231)FIFF_SUBAVE_FIRST"},
         {233, "(233)FIFF_NAME"},
         {206, "(206)FIFF_DESCRIPTION"},
         {234, "(234)FIFF_DIG_STRING"}};

// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},
// {,},

 std::map<int,std::string> Fiff::Formatting::_tagType
 {{3, "(3)int"}};

const std::map<int,std::string>& Fiff::Formatting::tagKinds()
{
  return _tagKind;
}

const std::map<int,std::string>& Fiff::Formatting::tagTypes()
{
  return _tagType;
}

void Fiff::Formatting::replaceIdWithString(std::stringstream& stream,
                         const std::map<int,std::string>& map,
                         int id)
{
  auto mapEntry = map.find(id);
  if (mapEntry != map.end()) {
    stream << mapEntry->second;
  } else {
    stream << id;
  }
}

std::string Fiff::Formatting::humanReadable(const Fiff::Tag& tag){
  std::stringstream out;

  replaceIdWithString(out, _tagKind, tag.kind);
  out << ", data type ";
  replaceIdWithString(out, _tagType, tag.type);
  out << ", ";
  out << tag.size << " bytes, next:" << tag.next;

  return out.str();
}

