#include <QWidget>
#include <QApplication>

#include "Main_Window.h"
#include "Graphics_View.h"

int main(int argc, char** argv) {
	QApplication App{ argc, argv };	

	Main_Window wnd;
	wnd.show();    

	return App.exec();
}