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

        float view_offset = static_cast<double>(rectangle.height()) / static_cast<double>(number_of_views + 1);

        QPainter painter(this);
        painter.setBrush(QBrush(Qt::white));
        painter.drawRect(rectangle);

        for(auto h = 0; h < number_of_views; ++h){
            auto* view = views[h];

            auto center_left = QPoint(rectangle.bottomLeft().rx(), view_offset * (h + 1));

            float x_offeset = center_left.rx();
            float y_offeset = center_left.ry();
            float x_step = static_cast<float>(rectangle.width() / static_cast<float>(view->max_domain) - static_cast<float>(view->min_domain));

            QPainterPath path;

            float current_x = x_offeset;
            path.moveTo(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(view->source->data_ptr)[0] * view->scale * -1 + y_offeset));
            for(auto i = 1; i < view->max_domain - view->min_domain; ++i){
                if(i >= (int)view->source->length){
                    break;
                }
                current_x += x_step;
                path.lineTo(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(view->source->data_ptr)[i] * view->scale * -1 + y_offeset));
            }

            painter.setBrush(QBrush(Qt::blue));
            painter.drawPath(path);
        }
    }

    (void)event;
//    for(auto& view : views){

//    }
}

