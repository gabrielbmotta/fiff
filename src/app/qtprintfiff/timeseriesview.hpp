#ifndef TIMESERIESVIEW_H
#define TIMESERIESVIEW_H

#include <QObject>
#include <QWidget>

#include <string>
#include <QPaintDevice>

struct DataSource{
    enum DataType{
        type_float_32 = 0,
        type_int_64 = 1,
        type_int_32 = 10,
    };

    int id;
    std::string id_name;

    void* data_ptr;
    DataType data_type;
    size_t length;
    size_t offset;
};

struct DataViewParam{
    DataSource* source;

    double min_range;
    double max_range;
    int min_domain;
    int max_domain;

    float scale;

    std::string title;
};

class TimeSeriesView : public QWidget
{
    Q_OBJECT

public:
    TimeSeriesView();
    virtual void paintEvent(QPaintEvent* event) override;


    std::vector<DataViewParam*> views;
};

#endif // TIMESERIESVIEW_H
