#include <QWidget>
#include <QApplication>

#include "Main_Window.h"
#include "Graphics_View.h"

int main(int argc, char** argv) {
	QApplication App{ argc, argv };

	QSurfaceFormat format;
	format.setRenderableType(QSurfaceFormat::OpenGL); // ���������� ��� ���������� OpenGL
	format.setProfile(QSurfaceFormat::CoreProfile); // ������������ Core Profile OpenGL
	format.setVersion(3, 3); // ���������� ������ OpenGL 3.3

	Main_Window wnd;
	wnd.show();
    

	return App.exec();
}