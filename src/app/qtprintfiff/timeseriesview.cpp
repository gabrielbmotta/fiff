#include "timeseriesview.hpp"
#include <QLabel>
#include <QVBoxLayout>

#include <QPainter>
#include <QPainterPath>
#include <QBrush>

TimeSeriesView::TimeSeriesView()
{
    this->setLayout(new QVBoxLayout());
    this->layout()->addWidget(new QLabel("Test Label"));
}

void TimeSeriesView::paintEvent(QPaintEvent* event)
{
    if (!views.empty()){
        auto* view = views.front();
        QPainter painter(this);

        auto rectangle = this->rect();

        auto bottom_left = rectangle.bottomLeft();
        auto top_right = rectangle.topRight();

        auto center_left = QPoint(bottom_left.rx(), (bottom_left.ry() + top_right.ry()) / 2);
        float x_offeset = center_left.rx();
        float y_offeset = center_left.ry();
        float x_step = static_cast<float>(view->max_domain) - static_cast<float>(view->min_domain) / static_cast<float>(rectangle.width());

        QPainterPath path;

        float current_x = x_offeset;
        path.moveTo(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(view->source->data_ptr)[0] * view->scale * -1 + y_offeset));
        for(auto i = 1; i < view->max_domain - view->min_domain; ++i){
            current_x += x_step;
            path.lineTo(static_cast<double>(current_x), static_cast<double>(static_cast<float*>(view->source->data_ptr)[i] * view->scale * -1 + y_offeset));
        }

        painter.drawPath(path);
    }

    (void)event;
//    for(auto& view : views){

//    }
}

