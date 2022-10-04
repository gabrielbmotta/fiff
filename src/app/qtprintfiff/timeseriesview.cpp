#include "timeseriesview.hpp"
#include <QLabel>
#include <QVBoxLayout>
#include <QScrollBar>

#include <QPainter>
#include <QPainterPath>
#include <QBrush>

#include "tracer.hpp"

TimeSeriesViewCanvas::TimeSeriesViewCanvas()
:plot_line_color(Qt::blue)
,background_color(Qt::white)
,axis_color(Qt::lightGray)
,text_color(Qt::black)
,max_channels_shown(15)
,max_points_shown(300)
{
    MNE_TRACE();
}

class TimeSeriesViewScrollBar : QScrollBar
{

};

void TimeSeriesViewCanvas::paintEvent(QPaintEvent* event)
{
    MNE_TRACE();

    if (!views.empty()){
        QPainter painter(this);
        auto rectangle = paintPlotArea(&painter);

        int number_of_views = std::min(static_cast<int>(views.size()), max_channels_shown);
        float separation = static_cast<double>(rectangle.height()) / static_cast<double>(number_of_views + 1);

        QPixmap map(rectangle.width(), rectangle.height());
        map.fill(background_color);
        QPainter pixmap_painter(&map);

        for(auto h = 0; h < number_of_views; ++h){
            auto* view = views[h];

            auto offset = QPoint(rectangle.left(), rectangle.top() + separation * (h + 1));
            float x_offset = offset.rx();
            float y_offset = offset.ry();

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

void TimeSeriesViewCanvas::paintBackground(QPainter* painter)
{
    MNE_TRACE();

    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::white);
    painter->drawRect(this->rect());
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

void TimeSeriesViewCanvas::paintTimeSeries(QPainter* painter, QRect* rect, DataViewParam* param, float x_offset, float y_offset)
{
    MNE_TRACE();

    painter->setPen(plot_line_color);
    painter->setBrush(Qt::transparent);

    x_offset -= rect->left();
    y_offset -= rect->top();
    double x_step = static_cast<double>(rect->width() / static_cast<double>(param->max_domain) - static_cast<double>(param->min_domain));
    double current_x = static_cast<double>(x_offset);

    auto limit = std::min(param->max_domain - param->min_domain, (int)param->source->length);

    QPointF last = QPointF(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(param->source->data_ptr)[0] * param->scale * -1 + y_offset));
    for(auto i = 1; i < limit; ++i){
        MNE_TRACE();
        current_x += x_step;
        QPointF next = QPointF(current_x, static_cast<double>(static_cast<float*>(param->source->data_ptr)[i] * param->scale * -1 + y_offset));
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

QRect TimeSeriesViewCanvas::paintPlotArea(QPainter* painter)
{
    MNE_TRACE();

    (void)painter;

    int long_diff = this->rect().width() * 0.05;
    int short_diff = this->rect().height() * 0.02;

    auto inner_rect = this->rect().adjusted(long_diff, short_diff,
                                            -short_diff, -short_diff);

    painter->setBrush(background_color.darker(130));
    painter->setPen(Qt::black);
    painter->drawRect(this->rect());

    painter->setBrush(background_color);
    painter->drawRect(inner_rect);

    return inner_rect;
}

TimeSeriesView::TimeSeriesView(QWidget* parent)
: QWidget(parent)
, vc(new TimeSeriesViewCanvas)
, layout(new QVBoxLayout())
{
    this->setLayout(layout);
    layout->addWidget(vc);
    layout->setSpacing(0);
    layout->setMargin(0);

    layout->addWidget(new QScrollBar(Qt::Horizontal));
}

