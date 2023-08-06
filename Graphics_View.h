#pragma once

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>

#include <QMouseEvent>

#include "Modification_Mode.h"
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

	void mousePressEvent(QMouseEvent* p_event)	 override;
	void mouseMoveEvent(QMouseEvent* p_event)  noexcept	 override;
	void mouseReleaseEvent(QMouseEvent* p_event) override;
	void keyPressEvent(QKeyEvent* p_event)		 override;
	void keyReleaseEvent(QKeyEvent* p_event)	 override;

	void resizeEvent(QResizeEvent* p_event) override {
		//qDebug() << pE->size();
	}

public:

	Graphics_View(int mode, QWidget* parent = nullptr);
	void set_mode(int mode);
	QGraphicsScene* get_scene();

};

