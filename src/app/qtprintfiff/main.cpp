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

    QApplication a(argc, argv);

    constexpr size_t array_size = 1000;
    float my_data[array_size];

    for(size_t i = 0; i < array_size; ++i){
        my_data[i] = std::sin(i);
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
    data_view_param.scale = 10;
    data_view_param.title = "TEST";


    TimeSeriesView view;

    int num_channels = 32;
    for (int i = 0; i < num_channels; ++i){
        view.vc->views.push_back(&data_view_param);
    }

    view.show();

    auto ret = a.exec();

    MNE_TRACER_DISABLE;

    return ret;
}
