#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include <QMouseEvent>

#include "Move_Mode.h"
#include "Square_Mode.h"
#include "Rectangle_Mode.h"
#include "Triangle_Mode.h"
#include "Circle_Mode.h"

#include <QOpenGLWidget>

namespace mode {
	enum {
		Move, Square, Rectangle, Triangle, Circle,
	};
}

class Graphics_View : public QGraphicsView{
private:
	QGraphicsScene*		scene = nullptr;
	
	QVector<Application_Mode*> modes;
	int mode;

protected:

	void mousePressEvent(QMouseEvent* pE) override;
	void mouseMoveEvent(QMouseEvent* pE)  override;
	void mouseReleaseEvent(QMouseEvent* pE) override;

	void resizeEvent(QResizeEvent* pE) override {
		//qDebug() << pE->size();
	}

public:

	Graphics_View(int mode, QWidget* parent = nullptr);
	void set_mode(int mode);

};

