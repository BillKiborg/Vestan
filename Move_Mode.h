#pragma once
#include "Application_Mode.h"
#include "Graphics_View.h"

class Move_Mode : public Application_Mode {
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
	};

	bool cntr_flag = false;

	int mode = Default;

public:
	Move_Mode(Graphics_View* view)
		: Application_Mode{ view } {
		
	}

	void drawing(QMouseEvent* pE, QGraphicsScene* scene);

};

