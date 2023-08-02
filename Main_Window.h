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

#include "Graphics_View.h"

class Main_Window : public QMainWindow{
private:
	QTabWidget* tab_wgt = nullptr;
	int mode;

	QVector<QToolButton*> btns;

protected:
	void resizeEvent(QResizeEvent* pe) override {
		//qDebug() << pe->size();
	}

public:
	Main_Window();
};

