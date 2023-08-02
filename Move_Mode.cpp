#include "Move_Mode.h"

void Move_Mode::drawing(QMouseEvent* pE, QGraphicsScene* scene) {	

	if (pE->type() == QMouseEvent::MouseButtonPress && pE->button() == Qt::LeftButton) {
				
		pos_mouse_begin_move = pos_mouse_press = view->mapToScene(pE->pos());		

		auto item = scene->itemAt(pos_mouse_press, QTransform{ 1, 0, 0, 1, 0, 0 });		
		if (auto shape = static_cast<QAbstractGraphicsShapeItem*>(item); shape) {			

			if (mode == Default || mode == ShapeSelect) {

				shape->setPen(QPen{ QColor{253, 73, 173}, 5 });
				shape->update();

				if (!shapes.contains(shape)) {
					shapes.push_back(shape);
				}

				mode = ShapeSelect;
				qDebug() << "ShapeSelect";

				if (!cntr_flag) {

					shapes.removeIf([&shape](QAbstractGraphicsShapeItem* item) {
						if (shape != item) {
							item->setPen(QPen{ Qt::black, 1 });
							item->update();
							return true;
						}
						return false;
						});
				}

			}			
		}
		else {		

			qDebug() << "Default";
			mode = Default;

		}

	}
	else if (pE->type() == QMouseEvent::MouseMove && pE->buttons() & Qt::LeftButton) {
		
		if (mode == ShapeSelect || mode == Multiple_Selection) {

			auto current_pos = view->mapToScene(pE->pos());

			qreal
				dx = current_pos.x() - pos_mouse_begin_move.x(),
				dy = current_pos.y() - pos_mouse_begin_move.y();

			for (auto& shape : shapes) {
				shape->setPos(QPointF{ shape->scenePos().x() + dx, shape->scenePos().y() + dy });
				shape->update();
			}

			pos_mouse_begin_move = current_pos;
		}
		else if (mode == Default) {
			
			qDebug() << "Multiple_Selection";

			qreal x = qMin(pos_mouse_press.x(), view->mapToScene(pE->pos()).x());
			qreal y = qMin(pos_mouse_press.y(), view->mapToScene(pE->pos()).y());
			qreal width = qAbs(view->mapToScene(pE->pos()).x() - pos_mouse_press.x());
			qreal height = qAbs(view->mapToScene(pE->pos()).y() - pos_mouse_press.y());

			if (!rect_select) {
				rect_select = new QGraphicsRectItem(x, y, width, height);
				rect_select->setBrush(QBrush{ QColor{253, 73, 173, 150} });	
				
				scene->addItem(rect_select);
			}
			else {
				rect_select->setRect(x, y, width, height);
				rect_select->update();
			}

			QList<QGraphicsItem*> itemsInRect 
				= scene->items(rect_select->sceneBoundingRect(), Qt::IntersectsItemBoundingRect);

			for (auto& item : itemsInRect) {

				if (item == rect_select) continue;

				auto shape = static_cast<QAbstractGraphicsShapeItem*>(item);
				if (!shapes.contains(shape)) {					
					shape->setPen(QPen{ QColor{253, 73, 173}, 5 });
					shapes.push_back(shape);					
				}						
				
			}

			shapes.removeIf([&itemsInRect](QAbstractGraphicsShapeItem* shape) {
				if (!itemsInRect.contains(shape)) {
					shape->setPen(QPen{ Qt::black, 1 });
					shape->update();
					return true;
				}
				return false;
				});

		}

	}
	else if (pE->type() == QMouseEvent::MouseButtonRelease) {
		
		if (rect_select) {

			scene->removeItem(rect_select);
			delete rect_select;
			rect_select = nullptr;

			if (shapes.isEmpty()) {
				mode = Default;
				qDebug() << "Default";
			}
			else {
				mode = Multiple_Selection;
				qDebug() << "Multiple_Selection";
			}
			
		}

		if (mode == Default && pos_mouse_press == view->mapToScene(pE->pos())) {

			for (auto& shape : shapes) {
				shape->setPen(QPen{ Qt::black, 1 });
				shape->update();
			}

			shapes.clear();			

		}

	}
}

