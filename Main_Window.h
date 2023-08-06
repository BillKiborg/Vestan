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

#include "Graphics_View.h"
#include "Tool_Button.h"

#include <fstream>

class Main_Window : public QMainWindow{
private:
	QTabWidget* tab_wgt = nullptr;
	int mode;
	Tool_Button* bt_mode = nullptr;

	QVector<QToolButton*> btns;

protected:
	void resizeEvent(QResizeEvent* pe) override {
		//qDebug() << pe->size();
	}

public:
	Main_Window();
	void save();
	void save_as(QGraphicsScene* scene);
	void load();

};

