#include "timeseriesview.hpp"
#include <QLabel>
#include <QVBoxLayout>

#include <QPainter>
#include <QPainterPath>
#include <QBrush>

#include "tracer.hpp"

TimeSeriesView::TimeSeriesView()
:plot_line_color(Qt::blue)
,background_color(Qt::white)
,axis_color(Qt::lightGray)
,text_color(Qt::black)
{
    MNE_TRACE();
}

void TimeSeriesView::paintEvent(QPaintEvent* event)
{
    MNE_TRACE();

    if (!views.empty()){
        QPainter painter(this);
        auto rectangle = paintPlotArea(&painter);

        int number_of_views = views.size();
        float separation = static_cast<double>(rectangle.height()) / static_cast<double>(number_of_views + 1);

        for(auto h = 0; h < number_of_views; ++h){
            auto* view = views[h];

            auto offset = QPoint(rectangle.left(), rectangle.top() + separation * (h + 1));
            float x_offset = offset.rx();
            float y_offset = offset.ry();

            if(y_offset + 1 >= rectangle.height()){
                break;
            }

            paintAxis(&painter, &rectangle, x_offset, y_offset);
            paintTimeSeries(&painter, &rectangle, view, x_offset, y_offset);
            paintName(&painter, x_offset, y_offset, separation);
        }
    }

    (void)event;
}

void TimeSeriesView::paintBackground(QPainter* painter)
{
    MNE_TRACE();

    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::white);
    painter->drawRect(this->rect());
}

void TimeSeriesView::paintAxis(QPainter* painter, QRect* rect, float x_offset, float y_offset)
{
    MNE_TRACE();

    QPainterPath path;

    path.moveTo(static_cast<double>(x_offset), static_cast<double>(y_offset));
    path.lineTo(rect->right(), static_cast<double>(y_offset));

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(axis_color);
    painter->drawPath(path);
}

void TimeSeriesView::paintTimeSeries(QPainter* painter, QRect* rect, DataViewParam* param, float x_offset, float y_offset)
{
    MNE_TRACE();

    double x_step = static_cast<double>(rect->width() / static_cast<double>(param->max_domain) - static_cast<double>(param->min_domain));

    QPainterPath path;
    double current_x = static_cast<double>(x_offset);

    auto limit = std::min(param->max_domain - param->min_domain, (int)param->source->length);

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(plot_line_color);

    QPointF last = QPointF(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(param->source->data_ptr)[0] * param->scale * -1 + y_offset));

    path.moveTo(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(param->source->data_ptr)[0] * param->scale * -1 + y_offset));
    for(auto i = 1; i < limit; ++i){
        MNE_TRACE();
        current_x += x_step;
        QPointF next = QPointF(current_x, static_cast<double>(static_cast<float*>(param->source->data_ptr)[i] * param->scale * -1 + y_offset));
        painter->drawLine({last, next});
        last = next;
//        path.lineTo(current_x, static_cast<double>(static_cast<float*>(param->source->data_ptr)[i] * param->scale * -1 + y_offset));
    }
}

void TimeSeriesView::paintName(QPainter* painter, float x_offset, float y_offset, float space)
{
    MNE_TRACE();

    auto bounding_rect = QRect(this->rect().left(), y_offset - (space / 4), x_offset - 1, space / 2);

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(text_color);

    painter->drawText(bounding_rect, Qt::AlignRight | Qt::AlignVCenter,"TEST");
}

QRect TimeSeriesView::paintPlotArea(QPainter* painter)
{
    MNE_TRACE();

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


