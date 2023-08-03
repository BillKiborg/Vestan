#include "Graphics_View.h"

Graphics_View::Graphics_View(int mode, QWidget* parent) {

    this->mode = mode;

    modes.push_back(new Modification_Mode{this});
    modes.push_back(new Square_Mode{this});
    modes.push_back(new Rectangle_Mode{this});
    modes.push_back(new Triangle_Mode{this});
    modes.push_back(new Circle_Mode{this});
    
    scene = new QGraphicsScene;        
    scene->setSceneRect(0, 0, 1208, 725);    
    setScene(scene);

    setRenderHint(QPainter::Antialiasing, true);

    auto openGL_wgt = new QOpenGLWidget;

    QSurfaceFormat format;	
    format.setSamples(16); 
    openGL_wgt->setFormat(format);    

    setViewport(openGL_wgt);    
}

void Graphics_View::keyPressEvent(QKeyEvent* p_event) {
    modes[mode]->drawing(p_event, scene);
}

void Graphics_View::keyReleaseEvent(QKeyEvent* p_event) {
    modes[mode]->drawing(p_event, scene);
}

void Graphics_View::mouseReleaseEvent(QMouseEvent* p_event) {
    modes[mode]->drawing(p_event, scene);
}

void Graphics_View::mouseMoveEvent(QMouseEvent* p_event) {
    modes[mode]->drawing(p_event, scene);
}

void Graphics_View::mousePressEvent(QMouseEvent* p_event) {
    modes[mode]->drawing(p_event, scene);
}

void Graphics_View::set_mode(int mode) {
    this->mode = mode;
}