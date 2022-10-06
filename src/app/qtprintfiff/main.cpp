#include <fiff/input.hpp>
#include <fiff/formatting.hpp>
#include <utils/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include "tracer.hpp"

#include <iostream>
#include <string>
#include <cmath>

#include <timeseriesview.hpp>

#include <QApplication>

void printByTags(Fiff::Input& in,  std::vector<int> &tag_set);
void printByBlocks(Fiff::Input& in);

int main(int argc, char* argv[])
{
    MNE_TRACER_ENABLE(mne_trace_disp.json);
    MNE_TRACE();

    Core::CommandLineInput cmdin(argc, argv);

    std::string filePath = cmdin.getValueThatEndsWith(".fif");
    if(filePath.empty()){
      return 0;
    }

    auto inFile = Fiff::Input::fromFile(filePath);

    std::vector<Fiff::ChannelInfo> channels;
    std::vector<std::vector<float>> data;


    while(inFile.peekKind() != Fiff::Kind::ch_info){
        inFile.skipTag();
    }
    bool done = false;
    while(!done){
        auto tag = inFile.getTag();
        if(tag.kind == Fiff::Kind::ch_info){
            channels.push_back(static_cast<Fiff::ChannelInfo>(tag.data));
        } else {
            done = true;
            for (size_t i = 0; i < channels.size(); ++i){
                data.push_back(std::vector<float>{});
            }
        }
    }
    while(auto kind = inFile.peekKind() != Fiff::Kind::data_buffer){
        inFile.skipTag();
    }
    done = false;
    while(!done){
        auto tag = inFile.getTag();
        if(tag.kind == Fiff::Kind::data_buffer){
            auto* data_buff = reinterpret_cast<int16_t*>(tag.data.byteArray);
            auto len = tag.size / 2;
            for(int i = 0; i < len; ++i){
                auto chan = i % channels.size();
                data[chan].push_back(data_buff[i] * channels[chan].cal * channels[chan].range);
            }
        } else {
            done = true;
        }
    }

//    constexpr size_t array_size = 50000;
//    float my_data[array_size];

//    for(size_t i = 0; i < array_size; ++i){
//        my_data[i] = std::sin(i);
//    }

//    DataSource data_source;
//    data_source.data_ptr = my_data;
//    data_source.data_type = DataSource::type_float_32;
//    data_source.length = array_size;
//    data_source.offset = 0;

//   DataViewParam data_view_param;
//    data_view_param.source = &data_source;
//    data_view_param.scale = 10;
//    data_view_param.title = "TEST";

    std::cout << "Num Channels " << channels.size() << ", " << data.size() << "\n";
    std::cout << "Num samples " << data.front().size() << "\n";

    QApplication a(argc, argv);

    TimeSeriesView view;
    
//    for(size_t i = 0; i < channels.size(); ++i){
//        DataSource* src = new DataSource();
//        src->data_type = DataSource::DataType::type_float_32;
//        src->length = data[i].size();
//        src->offset = 0;
//        src->data_ptr = data[i].data();

//        DataViewParam* param = new DataViewParam();
//        param->source = src;
//        param->title = channels[i].ch_name.data();
//        param->scale = 10;

//        view.vc->views.push_back(param);
//    }

    DataSource* src = new DataSource();
    src->data_type = DataSource::DataType::type_float_32;
    src->length = data.front().size();
    src->offset = 0;
    src->data_ptr = data.front().data();

    DataViewParam* param = new DataViewParam();
    param->source = src;
    param->title = "test";
    param->scale = 10;

    view.vc->views.push_back(param);

//    int num_channels = 32;
//    for (int i = 0; i < num_channels; ++i){
//        view.vc->views.push_back(&data_view_param);
//    }

    view.vc->max_points_shown = 2000;
    view.scrollbar->setRange(0, data.front().size() - 2000);

    view.show();

    auto ret = a.exec();

    MNE_TRACER_DISABLE;

    return ret;
}
