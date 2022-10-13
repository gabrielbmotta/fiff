#ifndef TIMESERIESVIEW_H
#define TIMESERIESVIEW_H

#include <QObject>
#include <QWidget>

#include <string>
#include <QPaintDevice>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QSpinBox>
#include <QDoubleSpinBox>


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

struct FloatControl{
    QWidget* widget;
    QDoubleSpinBox* spin_box;
};

struct IntControl{
    QWidget* widget;
    QSpinBox* spin_box;
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



    QColor plot_line_color;
    QColor background_color;
    QColor axis_color;
    QColor text_color;

    float sample_freq;

    int max_channels_shown;
    int max_points_shown;
    int starting_point;
    int starting_channel;
    int spacer_separation;
    float channel_title_margin_percentage;

private:
    void paintAxis(QPainter* painter, QRect* rect, float x_offset, float y_offset);
    void paintTimeSeries(QPainter* painter, QRect* rect, DataChannel* param, float x_offset, float y_offset);
    void paintName(QPainter* painter, DataChannel* param, float x_offset, float y_offset, float space);
    void paintSpacers(QPainter* painter, QRect* rect);

    QRect paintPlotArea(QPainter* painter);

public slots:
    void setStartingPoint(int start_offset);
    void setStartingChannel(int chan_offset);
    void setMaxNumPointsShown(int num_points);
};

class TimeSeriesView : public QWidget
{
    Q_OBJECT

public:
    TimeSeriesView(QWidget* parent = nullptr);

    TimeSeriesViewCanvas* vc;
    QScrollBar* hor_scrollbar;
    QScrollBar* ver_scrollbar;

    QWidget* getSettings();

private:
    void createSettings();
    QWidget* createScaleSettings();
    QWidget* createViewSettings();

    FloatControl createFloatControls(std::string name, size_t min, size_t max, float default_val);
    IntControl createIntControls(std::string name, size_t min, size_t max, int default_val);

    QWidget* settings;

signals:
    void viewWidthChanged(int view_width);

public slots:
    void setScaleForTag(float scale, std::string tag);
    void setMaxChannelsShown(int chans);
    void setMaxPointsShown(int points);
};

#endif // TIMESERIESVIEW_H
