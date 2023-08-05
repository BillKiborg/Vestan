#pragma once
#include "Application_Mode.h"
#include "Graphics_View.h"

class Modification_Mode : public Application_Mode {
private:

	QList<QAbstractGraphicsShapeItem*> shapes;	
	QPointF
		pos_mouse_press,
		pos_mouse_begin_move,
		pos_mouse_release;

	QGraphicsRectItem* rect_select = nullptr;

	enum {
		Default,
		ShapeSelect,
		//Move,
		Multiple_Selection,
		Rotate,
		Clone,
		MoveClone
	};

	bool cntr_flag = false;
	int  mode = Default;

	void move(QMouseEvent* p_event, QGraphicsScene* scene);
	void rotate(QMouseEvent* p_event);
	void selection();
	void clone(QGraphicsScene* scene);
	
public:
	Modification_Mode(Graphics_View* view)
		: Application_Mode{ view } {
		
	}

	void drawing(QInputEvent* p_event, QGraphicsScene* scene);

};

