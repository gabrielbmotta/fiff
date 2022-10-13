#include "timeseriesview.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollBar>
#include <QHBoxLayout>

#include <QGroupBox>
#include <QPainter>
#include <QPainterPath>
#include <QBrush>
#include <QDoubleSpinBox>
#include <QGridLayout>

#include <set>

TimeSeriesViewCanvas::TimeSeriesViewCanvas()
: plot_line_color(Qt::blue)
, background_color(Qt::white)
, axis_color(Qt::lightGray)
, text_color(Qt::black)
, sample_freq(500)
, max_channels_shown(32)
, max_points_shown(2000)
, starting_point(0)
, spacer_separation(600)
, channel_title_margin_percentage(.06f)
{

}

void TimeSeriesViewCanvas::paintEvent(QPaintEvent* event)
{
    (void)event;

    if (!channels.empty()){

        QPainter painter(this);
        auto rectangle = paintPlotArea(&painter);

        int number_of_channels = std::min(static_cast<int>(channels.size()), max_channels_shown);
        float separation = static_cast<double>(rectangle.height()) / static_cast<double>(number_of_channels + 1);

        QPixmap map(rectangle.width(), rectangle.height());
        map.fill(background_color);
        QPainter pixmap_painter(&map);
        paintSpacers(&pixmap_painter, &rectangle);

        auto offset = (static_cast<int>(channels.size()) >= starting_channel + max_channels_shown) ? starting_channel : 0;

        for(auto h = 0; h < number_of_channels; ++h){
            auto* view = channels[h + offset];

            auto offset = QPoint(rectangle.left(), rectangle.top() + separation * (h + 1));
            float x_offset = offset.x(), y_offset = offset.y();

            if(y_offset + 1 >= rectangle.height()){
                break;
            }

            paintAxis(&pixmap_painter, &rectangle, x_offset, y_offset);
            paintTimeSeries(&pixmap_painter, &rectangle, view, x_offset, y_offset);
            paintName(&painter, view, x_offset, y_offset, separation);
        }

        painter.drawPixmap(rectangle, map);
    }
}

void TimeSeriesViewCanvas::paintAxis(QPainter* painter, QRect* rect, float x_offset, float y_offset)
{
    x_offset -= rect->left();
    y_offset -= rect->top();

    painter->setPen(axis_color);
    painter->setBrush(Qt::transparent);
    painter->drawLine(static_cast<double>(x_offset), static_cast<double>(y_offset),rect->width(), static_cast<double>(y_offset));
}

void TimeSeriesViewCanvas::paintTimeSeries(QPainter* painter, QRect* rect, DataChannel* param, float x_offset, float y_offset)
{
    painter->setPen(plot_line_color);
    painter->setBrush(Qt::transparent);

    x_offset -= rect->left();
    y_offset -= rect->top();
    double domain = static_cast<double>(max_points_shown);
    double x_step = static_cast<double>(rect->width() / domain);
    double current_x = static_cast<double>(x_offset);

    auto limit = std::min(max_points_shown, (int)param->source->length - starting_point);

    QPointF last = QPointF(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(param->source->data_ptr)[starting_point] * param->scale * -1 + y_offset));
    for(auto i = 1; i < limit; ++i){

        current_x += x_step;
        QPointF next = QPointF(current_x, static_cast<double>(static_cast<float*>(param->source->data_ptr)[i + starting_point] * param->scale * -1 + y_offset));
        painter->drawLine({last, next});
        last = next;
    }
}

void TimeSeriesViewCanvas::paintName(QPainter* painter, DataChannel* param, float x_offset, float y_offset, float space)
{
    auto bounding_rect = QRect(this->rect().left(), y_offset - (space / 4), x_offset - 1, space / 2);

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(text_color);

    painter->drawText(bounding_rect, Qt::AlignRight | Qt::AlignVCenter, QString::fromStdString(param->title));
}

void TimeSeriesViewCanvas::paintSpacers(QPainter* painter, QRect* rect)
{
    double domain = static_cast<double>(max_points_shown);
    double x_step = static_cast<double>(rect->width() / domain);

    int draw_point = -1;

    for(auto i = 1; i < max_points_shown; ++i){

        if(!((i + starting_point) % spacer_separation)){
            draw_point = i;
            break;
        }
    }
    double current_x = x_step * draw_point;

    painter->setBrush(Qt::transparent);
    QPen pen;
    pen.setColor(Qt::gray);
    pen.setStyle(Qt::DashLine);
    painter->setPen(pen);
    while(draw_point < max_points_shown){
        painter->drawLine(static_cast<int>(current_x), rect->top(), static_cast<int>(current_x), rect->bottom());
        draw_point += spacer_separation;
        current_x += x_step * spacer_separation;
    }
}


QRect TimeSeriesViewCanvas::paintPlotArea(QPainter* painter)
{
    int long_diff = this->rect().width() * channel_title_margin_percentage;

    auto inner_rect = this->rect().adjusted(long_diff, 0,-0, -0);

    painter->setBrush(background_color.darker(130));
    painter->setPen(Qt::black);
    painter->drawRect(this->rect());

    painter->setBrush(background_color);
    painter->drawRect(inner_rect);

    return inner_rect;
}

void TimeSeriesViewCanvas::setStartingPoint(int start_offset)
{
    starting_point = start_offset;
    repaint();
}

void TimeSeriesViewCanvas::setStartingChannel(int chan_offset)
{
    starting_channel = chan_offset;
    repaint();
}

void TimeSeriesViewCanvas::setMaxNumPointsShown(int num_points)
{
    max_points_shown = num_points;
    repaint();
}

TimeSeriesView::TimeSeriesView(QWidget* parent)
: QWidget(parent)
, vc(new TimeSeriesViewCanvas)
, settings(nullptr)
{
    auto* layout = new QGridLayout();
    layout->addWidget(vc,0,0);

    this->setLayout(layout);
    layout->setSpacing(0);
    layout->setMargin(0);

    hor_scrollbar = new QScrollBar(Qt::Horizontal);
    layout->addWidget(hor_scrollbar);
    layout->addWidget(hor_scrollbar,1,0);

    ver_scrollbar = new QScrollBar(Qt::Vertical);
    layout->addWidget(ver_scrollbar);
    layout->addWidget(ver_scrollbar,0,1);

    connect(hor_scrollbar, &QAbstractSlider::sliderMoved,
            vc, &TimeSeriesViewCanvas::setStartingPoint);

    connect(ver_scrollbar, &QAbstractSlider::sliderMoved,
            vc, &TimeSeriesViewCanvas::setStartingChannel);

    connect(this, &TimeSeriesView::viewWidthChanged,
            vc, &TimeSeriesViewCanvas::setMaxNumPointsShown);
}

QWidget* TimeSeriesView::getSettings()
{
    if(!settings){
        createSettings();
    }

    return settings;
}

void TimeSeriesView::createSettings()
{
    settings = new QWidget();
    settings->setLayout(new QVBoxLayout());

    auto* view_section = createViewSettings();
    if(view_section){
        settings->layout()->addWidget(view_section);
    }

    auto* scale_section = createScaleSettings();
    if(scale_section){
        settings->layout()->addWidget(scale_section);
    }
}

QWidget* TimeSeriesView::createScaleSettings()
{
    std::set<std::string> used_tags;
    for (auto& channel : vc->channels){
        for (auto& tag : channel->tags){
            used_tags.insert(tag);
        }
    }

    if (!used_tags.empty()){
        auto* scale_section = new QGroupBox("Scale");
        scale_section->setLayout(new QVBoxLayout());
        settings->layout()->addWidget(scale_section);

        for (auto& tag : used_tags){
            auto control_widget = createFloatControls(tag, 1, 10000000000000000, 1);
            scale_section->layout()->addWidget(control_widget.widget);
            connect(control_widget.spin_box, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [tag, this](double val){setScaleForTag(val, tag);});
        }
        return scale_section;
    }
    return nullptr;
}

QWidget* TimeSeriesView::createViewSettings()
{
    auto* view_section = new QGroupBox("View");
    view_section->setLayout(new QVBoxLayout());
    settings->layout()->addWidget(view_section);

    auto num_samples_controls = createIntControls("Samples shown", 1, INT_MAX, vc->max_points_shown);
    connect(num_samples_controls.spin_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &TimeSeriesView::setMaxPointsShown);
    view_section->layout()->addWidget(num_samples_controls.widget);

    auto num_channels_controls = createIntControls("Channels shown", 1, INT_MAX, vc->max_channels_shown);
    connect(num_channels_controls.spin_box, static_cast<void (QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &TimeSeriesView::setMaxChannelsShown);
    view_section->layout()->addWidget(num_channels_controls.widget);


    return view_section;
}

FloatControl TimeSeriesView::createFloatControls(std::string name, size_t min, size_t max, float default_val)
{
    auto* control_widget = new QWidget();
    control_widget->setLayout(new QHBoxLayout());
    control_widget->layout()->addWidget(new QLabel(QString::fromStdString(name)));

    auto* spin_box = new QDoubleSpinBox();
    spin_box->setMinimum(min);
    spin_box->setMaximum(max);
    spin_box->setValue(static_cast<double>(default_val));
    control_widget->layout()->addWidget(spin_box);

    return {control_widget, spin_box};
}

IntControl TimeSeriesView::createIntControls(std::string name, size_t min, size_t max, int default_val)
{
    auto* control_widget = new QWidget();
    control_widget->setLayout(new QHBoxLayout());
    control_widget->layout()->addWidget(new QLabel(QString::fromStdString(name)));

    auto* spin_box = new QSpinBox();
    spin_box->setMinimum(min);
    spin_box->setMaximum(max);
    spin_box->setValue(static_cast<double>(default_val));
    control_widget->layout()->addWidget(spin_box);

    return {control_widget, spin_box};
}

void TimeSeriesView::setScaleForTag(float scale, std::string tag)
{
    for(auto& channel : vc->channels){
        if(std::find(channel->tags.begin(),channel->tags.end(), tag) != channel->tags.end()){
            channel->scale = scale;
        }
    }
    repaint();
}

void TimeSeriesView::setMaxChannelsShown(int chans)
{
    vc->max_channels_shown = chans;
    ver_scrollbar->setRange(0, vc->channels.size() - chans);
    repaint();
}

void TimeSeriesView::setMaxPointsShown(int points)
{
    vc->max_points_shown = points;
    hor_scrollbar->setRange(0, vc->channels.front()->source->length - points);
    repaint();
}
