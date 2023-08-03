#include "Main_Window.h"

Main_Window::Main_Window() {

	mode = mode::Square;
	setMinimumSize(1028, 647);

	QMenuBar* menubar = new QMenuBar{ this };
	QMenu* file_menu  = menubar->addMenu("File");

	QAction* new_action		= new QAction{ "New", this };
	QAction* load_action	= new QAction{ "Load", this };
	QAction* save_action	= new QAction{ "Save", this };
	QAction* save_as_action = new QAction{ "Save As", this };
	QAction* exit_action	= new QAction{ "Exit", this };

	file_menu->addAction(new_action);
	file_menu->addAction(load_action);
	file_menu->addAction(save_action);
	file_menu->addAction(save_as_action);
	file_menu->addAction(exit_action);	

	this->tab_wgt = new QTabWidget;
	tab_wgt->addTab(new Graphics_View{ mode }, "Новый");
	setCentralWidget(tab_wgt);
	
	QObject::connect(
		new_action, &QAction::triggered,
		[this] {
			tab_wgt->addTab(new Graphics_View{mode}, "Новый");
			tab_wgt->setCurrentIndex(tab_wgt->count() - 1);
		});	

	QToolBar* toolbar = new QToolBar{ "Toolbar", this };
	addToolBar(toolbar);
	
	auto bt_move = new QToolButton;
	bt_move->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Move.png" });
	toolbar->addWidget(bt_move);

	btns.push_back(bt_move);

	QObject::connect(
		bt_move, &QToolButton::clicked,
		[this] {
			qDebug() << "Move--------------------------------";
			//btns[mode]->setIcon(QIcon{""});
			for (int i = 0; i < tab_wgt->count(); ++i) {
				mode = mode::Move;
				//btns[mode]->setIcon(QIcon{ "" });
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});

	auto bt_square = new QToolButton;
	bt_square->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Square.png" });
	toolbar->addWidget(bt_square);
	
	btns.push_back(bt_square);

	QObject::connect(
		bt_square, &QToolButton::clicked,
		[this] {
			qDebug() << "Square--------------------------------";
			mode = mode::Square;
			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});

	auto bt_rectangle = new QToolButton;
	bt_rectangle->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Rectangle.png" });
	toolbar->addWidget(bt_rectangle);

	btns.push_back(bt_rectangle);

	QObject::connect(
		bt_rectangle, &QToolButton::clicked,
		[this] {
			qDebug() << "Rectangle";
			mode = mode::Rectangle;
			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});

	auto bt_triangle = new QToolButton;
	bt_triangle->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Triangle.png" });
	toolbar->addWidget(bt_triangle);

	btns.push_back(bt_triangle);

	QObject::connect(
		bt_triangle, &QToolButton::clicked,
		[this] {
			qDebug() << "Triangle";
			mode = mode::Triangle;
			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});
	
	auto bt_circle = new QToolButton;
	bt_circle->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Circle.png" });
	toolbar->addWidget(bt_circle);	

	btns.push_back(bt_circle);

	QObject::connect(
		bt_circle, &QToolButton::clicked,
		[this] {
			qDebug() << "Circle";
			mode = mode::Circle;
			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});

	setMenuBar(menubar);
}