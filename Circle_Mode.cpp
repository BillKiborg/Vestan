#include "Circle_Mode.h"

void Circle_Mode::drawing(QMouseEvent* pE, QGraphicsScene* scene) {

    if (pE->type() == QMouseEvent::MouseButtonPress && pE->button() == Qt::LeftButton) {

        pos_mouse_press = view->mapToScene(pE->pos());

    }
    else if (pE->type() == QMouseEvent::MouseMove) {

        auto current_pos = view->mapToScene(pE->pos());
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
    else if (pE->type() == QMouseEvent::MouseButtonRelease) {
        circle = nullptr;
    }    

}