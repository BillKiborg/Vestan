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
		Move,
		Multiple_Selection,
		Rotate,
	};

	bool cntr_flag = false;
	int  mode = Default;

	enum {
		clockwise,
		counter_clockwise,
	};

	bool direction = true;

public:
	Modification_Mode(Graphics_View* view)
		: Application_Mode{ view } {
		
	}

	void drawing(QInputEvent* p_event, QGraphicsScene* scene);

};

