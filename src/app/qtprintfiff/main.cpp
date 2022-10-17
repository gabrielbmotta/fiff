#include <fiff/input.hpp>
#include <fiff/formatting.hpp>
#include <utils/commandlineinput.hpp>
#include <core/stringmanip.hpp>
#include <qtui/timeseriesview.hpp>

#include <iostream>
#include <string>
#include <cmath>
#include <set>

#include <QApplication>

void printByTags(Fiff::Input& in,  std::vector<int> &tag_set);
void printByBlocks(Fiff::Input& in);

int main(int argc, char* argv[])
{
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
    while(inFile.peekKind() != Fiff::Kind::data_buffer){
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

    std::cout << "Num Channels " << channels.size() << ", " << data.size() << "\n";
    std::cout << "Num samples " << data.front().size() << "\n";

    QApplication a(argc, argv);

    TimeSeriesView view;

    std::set<std::string> used_tags;
    
    for(size_t i = 0; i < channels.size(); ++i){
        DataSource* src = new DataSource();
        src->data_type = DataSource::DataType::type_float_32;
        src->length = data[i].size();
        src->offset = 0;
        src->data_ptr = data[i].data();

        DataChannel* param = new DataChannel();
        param->source = src;
        param->title = channels[i].ch_name.data();

        param->scale = 1.f;

        switch(channels[i].chpos.coil_type){
        case Fiff::CoilType::vv_planar_w:
        case Fiff::CoilType::vv_planar_t1:
        case Fiff::CoilType::vv_planar_t2:
        case Fiff::CoilType::vv_planar_t3:
            param->tags.push_back("grad");
            break;
        case Fiff::CoilType::vv_mag_w:
        case Fiff::CoilType::vv_mag_t1:
        case Fiff::CoilType::vv_mag_t2:
        case Fiff::CoilType::vv_mag_t3:
            param->tags.push_back("mag");
            break;
        case Fiff::CoilType::none:
            param->tags.push_back("none");
            break;
        case Fiff::CoilType::eeg:
            param->tags.push_back("eeg");
        }

        view.vc->channels.push_back(param);
    }

    view.setMaxChannelsShown(32);
    view.setMaxPointsShown(10000);

    view.show();

    auto* settings = view.getSettings();
    settings->show();

    auto ret = a.exec();

    return ret;
}
