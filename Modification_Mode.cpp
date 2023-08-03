#include "Modification_Mode.h"

void Modification_Mode::drawing(QInputEvent* _p_event, QGraphicsScene* scene) {

	if (auto key_event = dynamic_cast<QKeyEvent*>(_p_event); key_event) {
				
		if (key_event->key() == Qt::Key_Control && key_event->type() == QEvent::KeyPress) {			
			cntr_flag = true;
		}
		else if (key_event->key() == Qt::Key_Control && key_event->type() == QEvent::KeyRelease) {			
			cntr_flag = false;
		}
		return;
	}

	auto p_event = dynamic_cast<QMouseEvent*>(_p_event);
	if (!p_event) return;

	if (p_event->type() == QMouseEvent::MouseButtonPress && p_event->button() == Qt::LeftButton) {
				
		pos_mouse_begin_move = pos_mouse_press = view->mapToScene(p_event->pos());		

		auto item = scene->itemAt(pos_mouse_press, QTransform{ 1, 0, 0, 1, 0, 0 });		
		if (auto shape = static_cast<QAbstractGraphicsShapeItem*>(item); shape) {			

			if (mode == Multiple_Selection) {
				if (!shapes.contains(shape)) mode = Default;
			}

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
				else {
					qDebug() << "Multiple_Selection";
					mode = Multiple_Selection;
				}

			}			
		}
		else {		

			qDebug() << "Default";
			mode = Default;			

		}

	}
	else if (p_event->type() == QMouseEvent::MouseButtonPress && p_event->button() == Qt::RightButton) {
		
		for (auto& shape : shapes) {
			shape->setTransformOriginPoint(shape->boundingRect().center());
			shape->setRotation(45);
		}

		qDebug() << "shapes size: " << shapes.size();

	}
	else if (p_event->type() == QMouseEvent::MouseMove && p_event->buttons() & Qt::LeftButton) {
		
		if (mode == ShapeSelect || mode == Multiple_Selection) {

			auto current_pos = view->mapToScene(p_event->pos());

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

			qreal x = qMin(pos_mouse_press.x(), view->mapToScene(p_event->pos()).x());
			qreal y = qMin(pos_mouse_press.y(), view->mapToScene(p_event->pos()).y());
			qreal width = qAbs(view->mapToScene(p_event->pos()).x() - pos_mouse_press.x());
			qreal height = qAbs(view->mapToScene(p_event->pos()).y() - pos_mouse_press.y());

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

			if (!cntr_flag) {

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
			else {
				
				for (auto& item : scene->items()) {

					if (item == rect_select) continue;
					else if (auto shape = static_cast<QAbstractGraphicsShapeItem*>(item); itemsInRect.contains(item)) {
						
						shape->setPen(QPen{ QColor{253, 73, 173}, 5 });
						shape->update();
						
					}
					else if (shapes.contains(item)) {
						continue;						
					}
					else {
						shape->setPen(QPen{ Qt::black, 1 });
						shape->update();
					}

				}

			}
		}

	}
	else if (p_event->type() == QMouseEvent::MouseButtonRelease) {
		
		if (rect_select) {

			if (cntr_flag) {

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

			}

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

		if (mode == Default && pos_mouse_press == view->mapToScene(p_event->pos())) {

			for (auto& shape : shapes) {
				shape->setPen(QPen{ Qt::black, 1 });
				shape->update();
			}

			shapes.clear();			

		}

	}
}
