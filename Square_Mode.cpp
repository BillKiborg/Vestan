#include "Square_Mode.h"

void Square_Mode::drawing(QInputEvent* _p_event, QGraphicsScene* scene) {

	auto p_event = dynamic_cast<QMouseEvent*>(_p_event);
	if (!p_event) return;

	if (p_event->type() == QEvent::MouseButtonPress && p_event->button() == Qt::LeftButton) {

		pos_center = view->mapToScene(p_event->pos());
		//qDebug() << "pos_center sq: " << pos_center;

		square = new QGraphicsRectItem;
		square->setBrush(QColor{100, 255, 3});
		scene->addItem(square);	
		square->setPos(pos_center);
		
	}
	else if (p_event->type() == QEvent::MouseMove && p_event->buttons() & Qt::LeftButton) {
		
		auto current_pos = view->mapToScene(p_event->pos());
		qreal distance = sqrt(pow(pos_center.x() - current_pos.x(), 2) + pow(pos_center.y() - current_pos.y(), 2));
		qreal side = distance / 2;

		square->setRect(QRectF{0, 0, side, side });
		square->setPos(QPointF{ pos_center.x() - side / 2, pos_center.y() - side / 2});

	}
	else if (p_event->type() == QEvent::MouseButtonRelease) {
		
		if (square)	{
			//qDebug() << "square rect: " << square->rect();
			//qDebug() << "square pos: " << square->scenePos();
			square = nullptr;			
		}
	}
	
}
