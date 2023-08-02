#pragma once
#include "Application_Mode.h"
#include "Graphics_View.h"

class Square_Mode : public Application_Mode {
private:
	QPointF				pos_center;
	QGraphicsRectItem*	square = nullptr;

public:

	Square_Mode(Graphics_View* view)
		: Application_Mode{ view } {

	}

	void drawing(QMouseEvent* pE, QGraphicsScene* scene) override;

};

