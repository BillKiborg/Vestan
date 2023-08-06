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
    
    format.setRenderableType(QSurfaceFormat::OpenGL); 
    format.setProfile(QSurfaceFormat::CoreProfile); 
    format.setVersion(3, 3); 

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

void Graphics_View::mouseMoveEvent(QMouseEvent* p_event) noexcept {

    auto t1 = std::chrono::system_clock::now();
    modes[mode]->drawing(p_event, scene);
    auto t2 = std::chrono::system_clock::now();
    qDebug() 
        << "mouse move time: " 
        << std::chrono::duration_cast<std::chrono::milliseconds>(t2 - t1).count() / 1000.0
        << "s";

}

void Graphics_View::mousePressEvent(QMouseEvent* p_event) {
    modes[mode]->drawing(p_event, scene);
}

void Graphics_View::set_mode(int mode) {
    this->mode = mode;
}

QGraphicsScene* Graphics_View::get_scene() {
    return scene;
}