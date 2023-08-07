#pragma once
#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QTabWidget>
#include <QToolBar>

#include <QLabel>
#include <QPushButton>
#include <QResizeEvent>
#include <QToolButton>
#include <QFile>
#include <QFileDialog>
#include <QCoreApplication>
#include <QApplication>

#include "Graphics_View.h"
#include "Tool_Button.h"
#include "Tab_Widget.h"

#include <QTabBar>

class Main_Window : public QMainWindow{
private:
	Tab_Widget* tab_wgt = nullptr;
	int mode;
	Tool_Button* bt_mode = nullptr;

	QVector<QToolButton*> btns;

	QMenuBar  menubar;
	QMenu*    file_menu = nullptr;

	QAction* new_action		= nullptr;
	QAction* load_action	= nullptr;
	QAction* save_action	= nullptr;
	QAction* save_as_action = nullptr;
	QAction* exit_action	= nullptr;

	QToolBar*	toolbar = nullptr;

	Tool_Button* bt_move		= nullptr;
	Tool_Button* bt_square		= nullptr;
	Tool_Button* bt_triangle	= nullptr;
	Tool_Button* bt_circle		= nullptr;


protected:
	void resizeEvent(QResizeEvent* pe) override {
		//qDebug() << pe->size();
	}

public:
	Main_Window();
	~Main_Window();

	void save();
	QString save_as(QGraphicsScene* scene);
	void load();	

};

