#include "Rectangle_Mode.h"

void Rectangle_Mode::drawing(QMouseEvent* pE, QGraphicsScene* scene) {
	
	if (pE->type() == QMouseEvent::MouseButtonPress && pE->button() == Qt::LeftButton) {

		pos_mouse_press = view->mapToScene(pE->pos());

	}
	else if (pE->type() == QMouseEvent::MouseMove) {

		qreal x = qMin(pos_mouse_press.x(), view->mapToScene(pE->pos()).x());
		qreal y = qMin(pos_mouse_press.y(), view->mapToScene(pE->pos()).y());
		qreal width = qAbs(view->mapToScene(pE->pos()).x() - pos_mouse_press.x());
		qreal height = qAbs(view->mapToScene(pE->pos()).y() - pos_mouse_press.y());

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
	else if (pE->type() == QMouseEvent::MouseButtonRelease) {

		if (rectangle) {
			rectangle = nullptr;
		}

	}

}