#include "Modification_Mode.h"

void Modification_Mode::move(QMouseEvent* p_event, QGraphicsScene* scene) {

	if (mode == ShapeSelect || mode == Multiple_Selection || mode == MoveClone) {

		auto current_pos = view->mapToScene(p_event->pos());

		qreal
			dx = current_pos.x() - pos_mouse_begin_move.x(),
			dy = current_pos.y() - pos_mouse_begin_move.y();

		for (auto& shape : shapes) {
			shape->moveBy(dx, dy);
			shape->update();

			//qDebug() << "pos post move: " << shape->mapToScene(shape->boundingRect().center());

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

void Modification_Mode::rotate(QMouseEvent* p_event) {

	auto current_pos = view->mapToScene(p_event->pos());

	for (auto& shape : shapes) {

		if (auto triangle = dynamic_cast<QGraphicsPolygonItem*>(shape); triangle) {

			auto points_from_scene = triangle->mapToScene(triangle->polygon());

			QPointF center_from_scene;
			for (auto& point : points_from_scene) {
				center_from_scene += point;
			}
			center_from_scene /= points_from_scene.size();

			QTransform T1{ 1, 0, 0, 1, -center_from_scene.x(), -center_from_scene.y() };

			auto pos_mouse_begin_move_T = pos_mouse_begin_move * T1;
			auto current_pos_T = current_pos * T1;

			auto angle_BOx = atan2(current_pos_T.y(), current_pos_T.x()) * 180 / M_PI;
			auto angle_AOx = atan2(pos_mouse_begin_move_T.y(), pos_mouse_begin_move_T.x()) * 180 / M_PI;
			auto angle = angle_BOx - angle_AOx;

			auto points = triangle->polygon();
			QPointF center;
			for (auto& point : points) {
				center += point;
			}
			center /= points.size();

			triangle->setTransformOriginPoint(center);
			triangle->setRotation(triangle->rotation() + angle);

		}
		else {

			auto bounding_rect = shape->boundingRect();
			QPointF center = shape->mapToScene(bounding_rect.center());
			QTransform t1{ 1, 0, 0, 1, -center.x(), -center.y() };

			auto pos_mouse_begin_move_T = pos_mouse_begin_move * t1;
			auto current_pos_T = current_pos * t1;

			auto tan_current = current_pos_T.y() / current_pos_T.x();
			auto tan_begin_pos = pos_mouse_begin_move_T.y() / pos_mouse_begin_move_T.x();

			if (!isinf(tan_current) && !isinf(tan_begin_pos)
				&& !isnan(tan_current) && !isnan(tan_begin_pos)) {

				auto angle_BOx = atan(tan_current) * 180 / M_PI;
				auto angle_AOx = atan(tan_begin_pos) * 180 / M_PI;
				auto angle = angle_BOx - angle_AOx;								
				
				shape->setTransformOriginPoint(shape->boundingRect().center());
				shape->setRotation(shape->rotation() + angle);
				shape->update();
			}

		}
	}

	pos_mouse_begin_move = current_pos;

}

void Modification_Mode::clone(QGraphicsScene* scene) {

	qDebug() << "clone";
	for (auto& shape : shapes) {	
		
		if (typeid(*shape).name() == typeid(QGraphicsRectItem).name()) {

			auto new_shape = new QGraphicsRectItem;
			auto old_shape = static_cast<QGraphicsRectItem*>(shape);
			
			new_shape->setBrush(old_shape->brush());

			auto rotation = old_shape->rotation();
			old_shape->setTransformOriginPoint(old_shape->boundingRect().center());			
			old_shape->setRotation(0);
				
			new_shape->setRect(old_shape->rect());			
			new_shape->setPos(old_shape->mapToScene(0, 0));
			new_shape->setTransformOriginPoint(old_shape->boundingRect().center());
			new_shape->setRotation(rotation);			

			old_shape->setRotation(rotation);			

			scene->addItem(new_shape);
			shape = new_shape;
			shape->update();

		}
		else if (typeid(*shape).name() == typeid(QGraphicsEllipseItem).name()) {
						
			auto old_shape = static_cast<QGraphicsEllipseItem*>(shape);
			auto rotation = old_shape->rotation();

			old_shape->setTransformOriginPoint(old_shape->boundingRect().center());
			old_shape->setRotation(0);

			auto new_shape = new QGraphicsEllipseItem;
			new_shape->setRect(old_shape->rect());
			new_shape->setBrush(old_shape->brush());
			new_shape->setPos(old_shape->mapToScene(0, 0));
			new_shape->setTransformOriginPoint(old_shape->boundingRect().center());
			new_shape->setRotation(rotation);

			old_shape->setRotation(rotation);

			scene->addItem(new_shape);
			shape = new_shape;			

		}		
		else if (typeid(*shape).name() == typeid(QGraphicsPolygonItem).name()) {
						
			auto old_shape = static_cast<QGraphicsPolygonItem*>(shape);
			auto rotation = old_shape->rotation();			

			QPointF center;
			for (auto& point : old_shape->mapToScene(old_shape->polygon())) {
				center += point;
			}
			center /= old_shape->polygon().size();
			qDebug() << "\n\ncenter old: " << center;

			old_shape->setTransformOriginPoint(center);
			old_shape->setRotation(old_shape->rotation() - rotation);

			auto new_shape = new QGraphicsPolygonItem;
			new_shape->setBrush(old_shape->brush());
			new_shape->setPolygon(old_shape->polygon());
			new_shape->setPos(old_shape->mapToScene(0, 0));			

			scene->addItem(new_shape);

			old_shape->setTransformOriginPoint(old_shape->mapFromScene(center));
			old_shape->setRotation(rotation);
			new_shape->setTransformOriginPoint(new_shape->mapFromScene(center));
			new_shape->setRotation(rotation);
			
			shape = new_shape;									

		}
	}

	qDebug() << "MoveClone";
	mode = MoveClone;

}

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

	qDebug() << "current pos mouse: " << view->mapToScene(p_event->pos());

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
	else if (p_event->type() == QMouseEvent::MouseButtonPress && p_event->button() == Qt::MiddleButton) {

		qDebug() << "Clone";
		pos_mouse_begin_move = pos_mouse_press = view->mapToScene(p_event->pos());
		mode = Clone;

		clone(scene);

	}
	else if (p_event->type() == QMouseEvent::MouseButtonPress && p_event->button() == Qt::RightButton) {
				
		pos_mouse_begin_move = pos_mouse_press = view->mapToScene(p_event->pos());
		auto item = scene->itemAt(pos_mouse_press, QTransform{ 1, 0, 0, 1, 0, 0 });
		if (item) {
			qDebug() << "Rotate";
			mode = Rotate;
			pos_mouse_begin_move = pos_mouse_press = view->mapToScene(p_event->pos());
		}				
		
	}
	else if (p_event->type() == QMouseEvent::MouseMove && p_event->buttons() & Qt::MiddleButton) {

		if (mode == Clone) {
			clone(scene);
		}
		else if (mode == MoveClone) {
			move(p_event, scene);
		}

	}
	else if (p_event->type() == QMouseEvent::MouseMove && p_event->buttons() & Qt::RightButton && mode == Rotate) {
			
		rotate(p_event);		

	}
	else if (p_event->type() == QMouseEvent::MouseMove && p_event->buttons() & Qt::LeftButton) {
		
		move(p_event, scene);		

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

		if (mode == Rotate) {

			if (shapes.isEmpty()) {
				mode = Default;
				qDebug() << "Default";
			}
			else {
				mode = Multiple_Selection;
				qDebug() << "Multiple_Selection";
			}

		}

		if (mode == MoveClone) {
			for (auto& item : scene->items()) {
				static_cast<QAbstractGraphicsShapeItem*>(item)->setPen(QPen{ Qt::black, 1 });
				item->update();
			}
			shapes.clear();
			mode = Default;
		}

	}
}

