#include <fiff/input.hpp>
#include <fiff/formatting.hpp>
#include <utils/commandlineinput.hpp>
#include <core/stringmanip.hpp>

#include <iostream>
#include <string>

#include <timeseriesview.hpp>

#include <QApplication>

void printByTags(Fiff::Input& in,  std::vector<int> &tag_set);
void printByBlocks(Fiff::Input& in);

int main(int argc, char* argv[])
{
//  Core::CommandLineInput cmdin(argc, argv);

//  if(cmdin.tagExists("--help","-h")){
//    std::cout << "|---      printfiff      ---|\n\n"
//              << "Usage: printfiff /path/to/file.fif [--tag-kind kind1,kind1,...]\n\n"
//              << "-k --tag-kind <input>\t Prints only the tags with matching tag type number.\n\n"
//              << "-h --help \t\t Prints help text.\n";
//  }

//  std::string filePath = cmdin.getValueThatEndsWith(".fif");
//  if(filePath.empty()){
//    return 0;
//  }

//  bool printBlocks = cmdin.tagExists("--blocks");
//  std::string tags = cmdin.getValueForTag("--tag-kind", "-k").second;

//  std::vector<int> tag_set;
//  if(!tags.empty()) {
//    tag_set = Core::StringManipulation::getVectorFrom<int>(tags, ',');
//  }

//  auto inFile = Fiff::Input::fromFile(filePath);

//  if(printBlocks){
//    printByBlocks(inFile);
//  } else {
//    printByTags(inFile, tag_set);
//  }


    QApplication a(argc, argv);

    constexpr size_t array_size = 1000;
    float my_data[array_size];

    for(size_t i = 0; i < array_size; ++i){
        my_data[i] = static_cast<float>(i);
    }

    DataSource data_source;
    data_source.data_ptr = my_data;
    data_source.data_type = DataSource::type_float_32;
    data_source.length = array_size;
    data_source.offset = 0;

    DataViewParam data_view_param;
    data_view_param.source = &data_source;
    data_view_param.min_domain = 0;
    data_view_param.max_domain = array_size;
    data_view_param.scale = 100;


    TimeSeriesView view;
    view.views.push_back(&data_view_param);
    view.show();

    return a.exec();
}

void printByTags(Fiff::Input& in,  std::vector<int> &tag_set)
{
  std::string padding = "  ";
  int indent = 0;
  while(!in.atEnd()){
    auto tag = in.getTag();
    if(!tag_set.empty() &&  std::find(tag_set.begin(), tag_set.end(), static_cast<int32_t>(tag.kind)) == tag_set.end()){
      continue;
    }

    if (tag.kind == Fiff::Kind::block_end){
      --indent;
    }
    for (int i = 0 ; i < indent ; ++i){
      std::cout << padding;
    }
    std::cout << Fiff::Formatting::asString(tag);
    std::cout << "\n";
    if(tag.kind == Fiff::Kind::block_start){
      ++indent;
    }
  }
}

void printByBlocks(Fiff::Input& in)
{
  std::string padding = "  ";
  int indent = 0;
  while(!in.atEnd()){
    auto tag = in.getTag();
      
      if (tag.kind == Fiff::Kind::block_start){
        for (int i = 0 ; i < indent ; ++i){
          std::cout << padding;
        }
        std::cout << Fiff::Formatting::dataAsString(tag) << "\n";
        indent++;
      }
      else if(tag.kind == Fiff::Kind::block_end){
        indent--;
      }
  }
}
