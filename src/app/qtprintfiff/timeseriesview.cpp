#include "timeseriesview.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollBar>

#include <QPainter>
#include <QPainterPath>
#include <QBrush>
#include <QDoubleSpinBox>

#include <set>

#include "tracer.hpp"

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
{
    MNE_TRACE();
}

void TimeSeriesViewCanvas::paintEvent(QPaintEvent* event)
{
    MNE_TRACE();

    if (!channels.empty()){

        QPainter painter(this);
        auto rectangle = paintPlotArea(&painter);

        int number_of_views = std::min(static_cast<int>(channels.size()), max_channels_shown);
        float separation = static_cast<double>(rectangle.height()) / static_cast<double>(number_of_views + 1);

        QPixmap map(rectangle.width(), rectangle.height());
        map.fill(background_color);
        QPainter pixmap_painter(&map);
        paintSpacers(&pixmap_painter, &rectangle);

        for(auto h = 0; h < number_of_views; ++h){
            auto* view = channels[h];

            auto offset = QPoint(rectangle.left(), rectangle.top() + separation * (h + 1));
            float x_offset = offset.x(), y_offset = offset.y();

            if(y_offset + 1 >= rectangle.height()){
                break;
            }

            paintAxis(&pixmap_painter, &rectangle, x_offset, y_offset);
            paintTimeSeries(&pixmap_painter, &rectangle, view, x_offset, y_offset);
            paintName(&painter, x_offset, y_offset, separation);
        }

        painter.drawPixmap(rectangle, map);
    }

    (void)event;
}

void TimeSeriesViewCanvas::paintAxis(QPainter* painter, QRect* rect, float x_offset, float y_offset)
{
    MNE_TRACE();

    x_offset -= rect->left();
    y_offset -= rect->top();

    painter->setPen(axis_color);
    painter->setBrush(Qt::transparent);
    painter->drawLine(static_cast<double>(x_offset), static_cast<double>(y_offset),rect->width(), static_cast<double>(y_offset));
}

void TimeSeriesViewCanvas::paintTimeSeries(QPainter* painter, QRect* rect, DataChannel* param, float x_offset, float y_offset)
{
    MNE_TRACE();

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
        MNE_TRACE();
        current_x += x_step;
        QPointF next = QPointF(current_x, static_cast<double>(static_cast<float*>(param->source->data_ptr)[i + starting_point] * param->scale * -1 + y_offset));
        painter->drawLine({last, next});
        last = next;
    }
}

void TimeSeriesViewCanvas::paintName(QPainter* painter, float x_offset, float y_offset, float space)
{
    MNE_TRACE();

    auto bounding_rect = QRect(this->rect().left(), y_offset - (space / 4), x_offset - 1, space / 2);

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(text_color);

    painter->drawText(bounding_rect, Qt::AlignRight | Qt::AlignVCenter,"TEST");
}

void TimeSeriesViewCanvas::paintSpacers(QPainter* painter, QRect* rect)
{
    double domain = static_cast<double>(max_points_shown);
    double x_step = static_cast<double>(rect->width() / domain);

    int draw_point = -1;

    for(auto i = 1; i < max_points_shown; ++i){
        MNE_TRACE();
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
    MNE_TRACE();

    (void)painter;

    int long_diff = this->rect().width() * 0.05;
//    int short_diff = this->rect().height() * 0.02;
//
//    auto inner_rect = this->rect().adjusted(long_diff, short_diff,
//                                            -short_diff, -short_diff);
    auto inner_rect = this->rect().adjusted(long_diff, 0,
                                            -0, -0);

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
    this->repaint();
}

void TimeSeriesViewCanvas::setMaxNumPointsShown(int num_points)
{
    max_points_shown = num_points;
    this->repaint();
}

TimeSeriesView::TimeSeriesView(QWidget* parent)
: QWidget(parent)
, vc(new TimeSeriesViewCanvas)
, layout(new QVBoxLayout())
, settings(nullptr)
{
    this->setLayout(layout);
    layout->addWidget(vc);
    layout->setSpacing(0);
    layout->setMargin(0);

    scrollbar = new QScrollBar(Qt::Horizontal);
    layout->addWidget(scrollbar);

    connect(scrollbar, &QAbstractSlider::sliderMoved,
            vc, &TimeSeriesViewCanvas::setStartingPoint);

    connect(this, &TimeSeriesView::viewWidthChanged,
            vc, &TimeSeriesViewCanvas::setMaxNumPointsShown);
}

QWidget* TimeSeriesView::getSettings()
{
    if(!settings){
        settings = new QWidget();
        settings->setLayout(new QVBoxLayout());

        std::set<std::string> used_tags;
        for (auto& channel : vc->channels){
            for (auto& tag : channel->tags){
                used_tags.insert(tag);
            }
        }

        for (auto& tag : used_tags){
            settings->layout()->addWidget(new QLabel(QString::fromStdString(tag)));
            auto spin_box = new QDoubleSpinBox();
            spin_box->setMinimum(1);
            spin_box->setMaximum(10000000000000000);
            settings->layout()->addWidget(spin_box);
            connect(spin_box, static_cast<void (QDoubleSpinBox::*)(double)>(&QDoubleSpinBox::valueChanged),
                    [tag, this](double val){setScaleForTag(val, tag);});
        }
    }

    return settings;
}

void TimeSeriesView::setScaleForTag(float scale, std::string tag)
{
    for(auto& channel : vc->channels){
        if(std::find(channel->tags.begin(),channel->tags.end(), tag) != channel->tags.end()){
            channel->scale = scale;
        }
    }

    this->repaint();
}
