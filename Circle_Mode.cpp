#include "Circle_Mode.h"

void Circle_Mode::drawing(QInputEvent* _p_event, QGraphicsScene* scene) {

    auto p_event = dynamic_cast<QMouseEvent*>(_p_event);
    if (!p_event) return;

    if (p_event->type() == QMouseEvent::MouseButtonPress && p_event->button() == Qt::LeftButton) {

        pos_mouse_press = view->mapToScene(p_event->pos());

    }
    else if (p_event->type() == QMouseEvent::MouseMove && p_event->buttons() & Qt::LeftButton) {

        auto current_pos = view->mapToScene(p_event->pos());
        qreal radius = sqrtf(pow(pos_mouse_press.x() - current_pos.x(), 2)
                            + pow(pos_mouse_press.y() - current_pos.y(), 2));

        if (!circle) {
            circle = new QGraphicsEllipseItem(pos_mouse_press.x() - radius, pos_mouse_press.y() - radius,
                radius * 2, radius * 2);

            circle->setBrush(Qt::green);              
            scene->addItem(circle);
        }
        else {
            circle->setRect(pos_mouse_press.x() - radius, pos_mouse_press.y() - radius, radius * 2, radius * 2);
            circle->update();
        }

    }
    else if (p_event->type() == QMouseEvent::MouseButtonRelease) {
        circle = nullptr;
    }    

}