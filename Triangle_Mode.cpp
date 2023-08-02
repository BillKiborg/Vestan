#include "Triangle_Mode.h"

void Triangle_Mode::drawing(QMouseEvent* pE, QGraphicsScene* scene) {    

    if (pE->type() == QMouseEvent::MouseButtonPress && pE->button() == Qt::LeftButton) {

        if (mode == point::p1) {

            p1 = new QPointF{ view->mapToScene(pE->pos()) };
            mode = point::p2;

            view->setMouseTracking(true);

            side_1 = new QGraphicsLineItem;
            side_1->setPen(QPen{ Qt::green });
            scene->addItem(side_1);

        }
        else if (mode == point::p2) {

            p2 = new QPointF{ view->mapToScene(pE->pos()) };
            mode = point::p3;

            side_2 = new QGraphicsLineItem;
            side_2->setPen(QPen{ Qt::green });
            scene->addItem(side_2);

        }
        else if (mode == point::p3) {
            p3 = new QPointF{ view->mapToScene(pE->pos()) };
            
            mode = point::p1;
            view->setMouseTracking(false);

            QPolygonF trianglePolygon;
            trianglePolygon << *p1 << *p2 << *p3;            

            QGraphicsPolygonItem* triangleItem = new QGraphicsPolygonItem(trianglePolygon);
            triangleItem->setBrush(Qt::green); 
            triangleItem->setFlags(QGraphicsItem::ItemIsMovable);
            scene->addItem(triangleItem);

            delete p1; p1 = nullptr;
            delete p2; p2 = nullptr;
            delete p3; p3 = nullptr;

            scene->removeItem(side_1);
            delete side_1; side_1 = nullptr;

            scene->removeItem(side_2);
            delete side_2; side_2 = nullptr;

        }        

    }
    else if (pE->type() == QEvent::MouseMove) {

        qDebug() << "move 1";

        auto current_pos = view->mapToScene(pE->pos());

        if (mode == point::p2) {
            side_1->setLine(QLineF{ p1->x(), p1->y(), current_pos.x(), current_pos.y() });
            side_1->update();            
        }
        else if (mode == point::p3) {
            side_2->setLine(QLineF{ p2->x(), p2->y(), current_pos.x(), current_pos.y() });
            side_2->update();
        }

    }    

}