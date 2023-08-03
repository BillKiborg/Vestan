#ifndef APPLICATION_MODE_H
#define APPLICATION_MODE_H

#include <QMouseEvent>
#include <QKeyEvent>
#include <QGraphicsScene>

class Graphics_View;

class Application_Mode {
protected:
	Graphics_View* view = nullptr;

public:

	virtual void drawing(QInputEvent*, QGraphicsScene*) = 0;
	virtual ~Application_Mode() = default;

	Application_Mode(Graphics_View* view) : view{view} {}	

};

#endif

