#include "Square_Mode.h"

void Square_Mode::drawing(QMouseEvent* pE, QGraphicsScene* scene) {

	if (pE->type() == QEvent::MouseButtonPress && pE->button() == Qt::LeftButton) {

		pos_center = view->mapToScene(pE->pos());
		//qDebug() << "pos_center sq: " << pos_center;

		square = new QGraphicsRectItem;
		square->setBrush(QColor{100, 255, 3});
		scene->addItem(square);	
		square->setPos(pos_center);
		
	}
	else if (pE->type() == QEvent::MouseMove) {
		
		auto current_pos = view->mapToScene(pE->pos());
		qreal distance = sqrt(pow(pos_center.x() - current_pos.x(), 2) + pow(pos_center.y() - current_pos.y(), 2));
		qreal side = distance / 2;

		square->setRect(QRectF{0, 0, side, side });
		square->setPos(QPointF{ pos_center.x() - side / 2, pos_center.y() - side / 2});

	}
	else if (pE->type() == QEvent::MouseButtonRelease) {
		
		if (square)	{
			//qDebug() << "square rect: " << square->rect();
			qDebug() << "square pos: " << square->scenePos();
			square = nullptr;			
		}
	}
	
}
