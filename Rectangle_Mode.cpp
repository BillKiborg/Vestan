#include "Rectangle_Mode.h"

void Rectangle_Mode::drawing(QInputEvent* _p_event, QGraphicsScene* scene) {
	
	auto p_event = dynamic_cast<QMouseEvent*>(_p_event);
	if (!p_event) return;

	if (p_event->type() == QMouseEvent::MouseButtonPress && p_event->button() == Qt::LeftButton) {

		pos_mouse_press = view->mapToScene(p_event->pos());

	}
	else if (p_event->type() == QMouseEvent::MouseMove && p_event->buttons() & Qt::LeftButton) {

		qreal x = qMin(pos_mouse_press.x(), view->mapToScene(p_event->pos()).x());
		qreal y = qMin(pos_mouse_press.y(), view->mapToScene(p_event->pos()).y());
		qreal width = qAbs(view->mapToScene(p_event->pos()).x() - pos_mouse_press.x());
		qreal height = qAbs(view->mapToScene(p_event->pos()).y() - pos_mouse_press.y());

		if (!rectangle){
			rectangle = new QGraphicsRectItem(x, y, width, height);
			rectangle->setBrush(QBrush{ Qt::green });
			scene->addItem(rectangle);
		}
		else {
			rectangle->setRect(x, y, width, height);			
			rectangle->update();
		}

	}
	else if (p_event->type() == QMouseEvent::MouseButtonRelease) {

		if (rectangle) {
			rectangle = nullptr;
		}

	}

}