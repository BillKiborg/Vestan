#pragma once
#include "Application_Mode.h"
#include "Graphics_View.h"

namespace point {
	enum{p1, p2, p3};
}

class Triangle_Mode : public Application_Mode {
private:

	QPointF* p1 = nullptr;
	QPointF* p2 = nullptr;
	QPointF* p3 = nullptr;	

	QGraphicsLineItem* side_1 = nullptr;
	QGraphicsLineItem* side_2 = nullptr;

	int mode = point::p1;

public:
	Triangle_Mode(Graphics_View* view)
		: Application_Mode{ view } {
	}

	void drawing(QMouseEvent* pE, QGraphicsScene* scene) override;

};

