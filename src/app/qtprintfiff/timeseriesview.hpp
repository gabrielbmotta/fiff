#ifndef TIMESERIESVIEW_H
#define TIMESERIESVIEW_H

#include <QObject>
#include <QWidget>

#include <string>
#include <QPaintDevice>
#include <QVBoxLayout>
#include <QScrollBar>

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

struct DataChannel{
    DataSource* source;
    float scale;
    std::string title;
    std::vector<std::string> tags;
};


class TimeSeriesViewScrollBar : QScrollBar
{
    TimeSeriesViewScrollBar();
};

class TimeSeriesViewCanvas : public QWidget
{
    Q_OBJECT

public:
    TimeSeriesViewCanvas();
    virtual void paintEvent(QPaintEvent* event) override;

    std::vector<DataChannel*> channels;

    void paintAxis(QPainter* painter, QRect* rect, float x_offset, float y_offset);
    void paintTimeSeries(QPainter* painter, QRect* rect, DataChannel* param, float x_offset, float y_offset);
    void paintName(QPainter* painter, float x_offset, float y_offset, float space);
    void paintSpacers(QPainter* painter, QRect* rect);

    QRect paintPlotArea(QPainter* painter);

    QColor plot_line_color;
    QColor background_color;
    QColor axis_color;
    QColor text_color;

    float sample_freq;

    int max_channels_shown;
    int max_points_shown;
    int starting_point;
    int spacer_separation;

public slots:
    void setStartingPoint(int start_offset);
    void setMaxNumPointsShown(int num_points);
};

class TimeSeriesView : public QWidget
{
    Q_OBJECT

public:
    TimeSeriesView(QWidget* parent = nullptr);

    TimeSeriesViewCanvas* vc;
    QVBoxLayout* layout;
    QScrollBar* scrollbar;

    QWidget* getSettings();

private:
    QWidget* settings;

signals:
    void viewWidthChanged(int view_width);

public slots:
    void setScaleForTag(float scale, std::string tag);
};

#endif // TIMESERIESVIEW_H
