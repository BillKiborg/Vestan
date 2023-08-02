#pragma once
#include "Application_Mode.h"
#include "Graphics_View.h"

class Rectangle_Mode : public Application_Mode {
private:

	QPointF pos_mouse_press;
	QGraphicsRectItem* rectangle = nullptr;

public:
	Rectangle_Mode(Graphics_View* view)
		: Application_Mode{ view } {
	}

	void drawing(QMouseEvent* pE, QGraphicsScene* scene) override;

};

