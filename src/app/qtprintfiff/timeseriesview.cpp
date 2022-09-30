#include "timeseriesview.hpp"
#include <QLabel>
#include <QVBoxLayout>

#include <QPainter>
#include <QPainterPath>
#include <QBrush>

TimeSeriesView::TimeSeriesView()
{
}

void TimeSeriesView::paintEvent(QPaintEvent* event)
{
    if (!views.empty()){
        int number_of_views = views.size();
        auto rectangle = this->rect();
        float separation = static_cast<double>(rectangle.height()) / static_cast<double>(number_of_views + 1);

        QPainter painter(this);

        paintBackground(&painter);

        for(auto h = 0; h < number_of_views; ++h){
            auto* view = views[h];

            auto offset = QPoint(rectangle.bottomLeft().rx(), separation * (h + 1));
            float x_offset = offset.rx();
            float y_offset = offset.ry();

            if(y_offset + 1 >= rectangle.height()){
                break;
            }

            paintAxis(&painter, x_offset, y_offset);
            paintTimeSeries(&painter, view, x_offset, y_offset);
            //paintName(&painter, x_offset, y_offset);
        }
    }

    (void)event;
}

void TimeSeriesView::paintBackground(QPainter* painter)
{
    painter->setBrush(QBrush(Qt::white));
    painter->setPen(Qt::white);
    painter->drawRect(this->rect());
}

void TimeSeriesView::paintAxis(QPainter* painter, float x_offset, float y_offset)
{
    QPainterPath path;

    path.moveTo(static_cast<double>(x_offset), static_cast<double>(y_offset));
    path.lineTo(this->rect().right(), static_cast<double>(y_offset));

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(Qt::lightGray);
    painter->drawPath(path);
}

void TimeSeriesView::paintTimeSeries(QPainter* painter, DataViewParam* param, float x_offset, float y_offset)
{
    float x_step = static_cast<float>(this->rect().width() / static_cast<float>(param->max_domain) - static_cast<float>(param->min_domain));

    QPainterPath path;
    float current_x = x_offset;
    path.moveTo(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(param->source->data_ptr)[0] * param->scale * -1 + y_offset));
    for(auto i = 1; i < param->max_domain - param->min_domain; ++i){
        if(i >= (int)param->source->length){
            break;
        }
        current_x += x_step;
        path.lineTo(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(param->source->data_ptr)[i] * param->scale * -1 + y_offset));
    }

    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(Qt::blue);
    painter->drawPath(path);
}

void TimeSeriesView::paintName(QPainter* painter, float x_offset, float y_offset)
{
    painter->setBrush(QBrush(Qt::transparent));
    painter->setPen(Qt::black);

    painter->drawText(QPointF{static_cast<double>(x_offset), static_cast<double>(y_offset)}, "TEST");
}

