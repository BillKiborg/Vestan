#include "Main_Window.h"

Main_Window::Main_Window() {

	mode = mode::Move;
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
	
	//--------------------------------------------------------------------------------
	auto bt_move = new Tool_Button;	
	
	bt_move->set_draw_function([bt = bt_move](bool activation) {				
		if (activation)
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Move_Focus.png" });
		else
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Move.png" });
		});		
		
	toolbar->addWidget(bt_move);
	btns.push_back(bt_move);

	QObject::connect(
		bt_move, &QToolButton::clicked,
		[this, bt = bt_move] {

			qDebug() << "Move----------------------------------";
			mode = mode::Move;
			bt_mode->set_activation(false);
			bt_mode = bt;
			bt_mode->set_activation(true);

			for (int i = 0; i < tab_wgt->count(); ++i) {								
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});

	bt_mode = bt_move;
	bt_mode->set_activation(true);
	

	//-------------------------------------------------------------------------------------------
	auto bt_square = new Tool_Button;	
	bt_square->set_draw_function([bt = bt_square](bool activation) {

		if (!activation)
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Square.png" });
		else
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Square_Focus.png" });

		});


	toolbar->addWidget(bt_square);
	btns.push_back(bt_square);

	QObject::connect(
		bt_square, &QToolButton::clicked,
		[this, bt = bt_square] {

			qDebug() << "Square--------------------------------";
			mode = mode::Square;
			bt_mode->set_activation(false);
			bt_mode = bt;
			bt_mode->set_activation(true);

			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});
	


	auto bt_rectangle = new Tool_Button;
	bt_rectangle->set_draw_function([bt = bt_rectangle](bool activation) {

		if (!activation) 
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Rectangle.png" });
		else
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Rectangle_Focus.png" });		

		});

	toolbar->addWidget(bt_rectangle);
	btns.push_back(bt_rectangle);

	QObject::connect(
		bt_rectangle, &QToolButton::clicked,
		[this, bt = bt_rectangle] {

			qDebug() << "Rectangle-----------------------------";
			mode = mode::Rectangle;
			bt_mode->set_activation(false);
			bt_mode = bt;
			bt_mode->set_activation(true);
			
			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});



	auto bt_triangle = new Tool_Button;
	bt_triangle->set_draw_function([bt = bt_triangle](bool activation) {
		if (activation)
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Triangle_Focus.png" });
		else
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Triangle.png" });
		});
	
	toolbar->addWidget(bt_triangle);
	btns.push_back(bt_triangle);

	QObject::connect(
		bt_triangle, &QToolButton::clicked,
		[this, bt = bt_triangle] {

			qDebug() << "Triangle------------------------------";
			bt_mode->set_activation(false);
			bt_mode = bt;
			bt_mode->set_activation(true);
			mode = mode::Triangle;

			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});
	


	auto bt_circle = new Tool_Button;
	bt_circle->set_draw_function([bt = bt_circle](bool activation) {

		if (!activation) 
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Circle.png" });
		else
			bt->setIcon(QIcon{ "C:\\Users\\Bill\\Desktop\\VS_C++\\Vestan\\Resource\\Circle_Focus.png" });

		});

	toolbar->addWidget(bt_circle);	
	btns.push_back(bt_circle);

	QObject::connect(
		bt_circle, &QToolButton::clicked,
		[this, bt = bt_circle] {

			qDebug() << "Circle--------------------------------";
			mode = mode::Circle;
			bt_mode->set_activation(false);
			bt_mode = bt;
			bt_mode->set_activation(true);

			for (int i = 0; i < tab_wgt->count(); ++i) {
				static_cast<Graphics_View*>(tab_wgt->widget(i))->set_mode(mode);
			}
		});

	setMenuBar(menubar);
}