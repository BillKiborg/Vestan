#pragma once
#include "Application_Mode.h"
#include "Graphics_View.h"

class Circle_Mode : public Application_Mode {
private:

	QPointF					pos_mouse_press;
	QGraphicsEllipseItem*	circle = nullptr;

	enum { center, radius, };
	int mode = center;

public:

	Circle_Mode(Graphics_View* view)
		: Application_Mode{ view } {
	}

	void drawing(QInputEvent* p_event, QGraphicsScene* scene) override;

};

