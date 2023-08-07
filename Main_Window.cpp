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

	this->tab_wgt = new Tab_Widget;

	auto test = new Graphics_View{ mode };
	auto test_action = new QAction{ "Test", test };
	test->addAction(test_action);

	QObject::connect(
		test_action, &QAction::triggered,
		[] {
			qDebug() << "Test";
		}
	);

	tab_wgt->addTab(test, "Новый");
	setCentralWidget(tab_wgt);
		
	QObject::connect(
		new_action, &QAction::triggered,
		[this] {
			tab_wgt->addTab(new Graphics_View{mode}, "Новый");
			tab_wgt->setCurrentIndex(tab_wgt->count() - 1);
		});	

	QObject::connect(
		load_action, &QAction::triggered,
		[this] {
			load();
		});

	QObject::connect(
		save_action, &QAction::triggered,
		[this] {
			qDebug() << "Save";
			save();
		});

	QObject::connect(
		save_as_action, &QAction::triggered,
		[this] {			
			auto scene = static_cast<Graphics_View*>(tab_wgt->widget(tab_wgt->currentIndex()))->get_scene();
			save_as(scene);
		});

	QToolBar* toolbar = new QToolBar{ "Toolbar", this };
	addToolBar(toolbar);
	
	//--------------------------------------------------------------------------------
	auto bt_move = new Tool_Button;	
				
	QDir  resource_path = QCoreApplication::applicationDirPath();	

	while (true) {		
		if (resource_path.dirName() == "Vestan") {			
			resource_path = resource_path.filePath("Resource");
			break;
		}
		resource_path.cdUp();
	}	

	bt_move->set_draw_function([bt = bt_move, resource_path](bool activation) {
				
		if (activation) 						
			bt->setIcon(QIcon{ resource_path.filePath("Move_Focus.png") });					
		else 			
			bt->setIcon(QIcon{ resource_path.filePath("Move.png") });
		
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
	bt_square->set_draw_function([bt = bt_square, resource_path](bool activation) {
		
		if (!activation) 		
			bt->setIcon(QIcon{ resource_path.filePath("Square.png") });		
		else 					
			bt->setIcon(QIcon{ resource_path.filePath("Square_Focus.png") });		

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
	bt_rectangle->set_draw_function([bt = bt_rectangle, resource_path](bool activation) {

		if (!activation) 			
			bt->setIcon(QIcon{ resource_path.filePath("Rectangle.png") });		
		else
			bt->setIcon(QIcon{ resource_path.filePath("Rectangle_Focus.png") });

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
	bt_triangle->set_draw_function([bt = bt_triangle, resource_path](bool activation) {
		if (activation)
			bt->setIcon(QIcon{ resource_path.filePath("Triangle_Focus.png") });			
		else
			bt->setIcon(QIcon{ resource_path.filePath("Triangle.png") });			
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
	bt_circle->set_draw_function([bt = bt_circle, resource_path](bool activation) {

		if (!activation) 
			bt->setIcon(QIcon{ resource_path.filePath("Circle.png") });			
		else
			bt->setIcon(QIcon{ resource_path.filePath("Circle_Focus.png") });			

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


void Main_Window::save() {

	auto view = static_cast<Graphics_View*>(tab_wgt->currentWidget());

	if (view->get_name() == "Новый") {		
		view->get_name() = save_as(view->get_scene());
		tab_wgt->setTabText(tab_wgt->currentIndex(), QDir{ view->get_name() }.dirName());
	}
	else {

		size_t count_item = view->get_scene()->items().count();
		//qDebug() << "count item scene: " << count_item;

		QFile file{ view->get_name()};
		if (file.open(QIODevice::WriteOnly)) {

			QDataStream stream{ &file };
			stream.setVersion(QDataStream::Qt_6_3);

			stream << count_item;
			for (size_t n = 0; n < count_item; n++) {

				auto shape = view->get_scene()->items().at(n);
				if (auto rectangle = dynamic_cast<QGraphicsRectItem*>(shape); rectangle) {

					stream << QString{typeid(*rectangle).name()};

					auto rotation = rectangle->rotation();
					rectangle->setTransformOriginPoint(rectangle->boundingRect().center());
					rectangle->setRotation(0);

					stream << rectangle->rect();
					stream << rectangle->mapToScene(0, 0);
					stream << rectangle->boundingRect().center();
					stream << rotation;

					rectangle->setRotation(rotation);

				}
				else if (auto circle = dynamic_cast<QGraphicsEllipseItem*>(shape); circle) {

					stream << QString{typeid(*circle).name()};

					auto rotation = circle->rotation();
					circle->setTransformOriginPoint(circle->boundingRect().center());
					circle->setRotation(0);

					stream << circle->rect();
					stream << circle->mapToScene(0, 0);
					stream << circle->boundingRect().center();
					stream << rotation;

					circle->setRotation(rotation);

				}
				else if (auto triangle = dynamic_cast<QGraphicsPolygonItem*>(shape); triangle) {

					stream << QString{typeid(*triangle).name()};

					auto rotation = triangle->rotation();

					QPointF center;
					for (auto& point : triangle->mapToScene(triangle->polygon())) {
						center += point;
					}
					center /= triangle->polygon().size();

					triangle->setTransformOriginPoint(center);
					triangle->setRotation(0);

					stream << triangle->polygon();
					stream << triangle->mapToScene(0, 0);
					stream << center;
					stream << rotation;

					triangle->setTransformOriginPoint(triangle->mapFromScene(center));
					triangle->setRotation(rotation);

				}

			}

			if (stream.status() != QDataStream::Ok) {
				qDebug() << "Fail Save";
			}

		}
		file.close();

	}

}


QString Main_Window::save_as(QGraphicsScene* scene) {
	
	QString selected_path = QFileDialog::getSaveFileName(
		this, "Folder", QDir::homePath() += "/Graphics_Saves"		
	);

	//qDebug() << "save path: " << selected_path;
	//-----------------------------------------------

	size_t count_item = scene->items().count();
	//qDebug() << "count item scene: " << count_item;
	
	QFile file{ selected_path };
	if (file.open(QIODevice::WriteOnly)) {

		QDataStream stream{ &file };
		stream.setVersion(QDataStream::Qt_6_3);		
				
		stream << count_item;
		for (size_t n = 0; n < count_item; n++) {

			auto shape = scene->items().at(n);
			if (auto rectangle = dynamic_cast<QGraphicsRectItem*>(shape); rectangle) {

				stream << QString{typeid(*rectangle).name()};				

				auto rotation = rectangle->rotation();
				rectangle->setTransformOriginPoint(rectangle->boundingRect().center());
				rectangle->setRotation(0);

				stream << rectangle->rect();
				stream << rectangle->mapToScene(0, 0);				
				stream << rectangle->boundingRect().center();
				stream << rotation;

				rectangle->setRotation(rotation);							

			}
			else if (auto circle = dynamic_cast<QGraphicsEllipseItem*>(shape); circle) {

				stream << QString{typeid(*circle).name()};

				auto rotation = circle->rotation();
				circle->setTransformOriginPoint(circle->boundingRect().center());
				circle->setRotation(0);

				stream << circle->rect();
				stream << circle->mapToScene(0, 0);
				stream << circle->boundingRect().center();
				stream << rotation;				

				circle->setRotation(rotation);

			}
			else if (auto triangle = dynamic_cast<QGraphicsPolygonItem*>(shape); triangle) {

				stream << QString{typeid(*triangle).name()};

				auto rotation = triangle->rotation();

				QPointF center;
				for (auto& point : triangle->mapToScene(triangle->polygon())) {
					center += point;
				}
				center /= triangle->polygon().size();

				triangle->setTransformOriginPoint(center);
				triangle->setRotation(0);

				stream << triangle->polygon();
				stream << triangle->mapToScene(0, 0);
				stream << center;
				stream << rotation;

				triangle->setTransformOriginPoint(triangle->mapFromScene(center));
				triangle->setRotation(rotation);
				
			}

		}
		
		if (stream.status() != QDataStream::Ok) {
			qDebug() << "Fail Save";
		}

	}
	file.close();
	return selected_path;

}

void Main_Window::load() {

	//qDebug() << "Load";
		
	auto view = new Graphics_View{ mode };	

	QString selected_path = QFileDialog::getOpenFileName(
		this, "Folder", QDir::homePath() += "/Graphics_Saves",
		"Binary Files (*)"
	);
	
	//qDebug() << "load file: " << selected_path;
	view->get_name() = selected_path;

	tab_wgt->addTab(view, QDir{ selected_path }.dirName());
	tab_wgt->setCurrentIndex(tab_wgt->count() - 1);

	QFile file{ selected_path };
	if (file.open(QIODevice::ReadOnly)) {
		QDataStream stream{ &file };
		stream.setVersion(QDataStream::Qt_6_3);

		size_t count_item; stream >> count_item;
		//qDebug() << "load count_item: " << count_item;

		for (int n = 0; n < count_item; n++) {
			
			QString type_name;		stream >> type_name;

			if (type_name == typeid(QGraphicsRectItem).name()) {

				QRectF	rect;			stream >> rect;
				QPointF pos_scene;		stream >> pos_scene;
				QPointF	center;			stream >> center;
				qreal	rotation;		stream >> rotation;

				QGraphicsRectItem* load_rect = new QGraphicsRectItem;
				load_rect->setBrush(Qt::green);
				load_rect->setRect(rect);
				load_rect->setPos(pos_scene);
				load_rect->setTransformOriginPoint(center);
				load_rect->setRotation(rotation);

				view->get_scene()->addItem(load_rect);

			}
			else if (type_name == typeid(QGraphicsEllipseItem).name()) {

				QRectF	rect;			stream >> rect;
				QPointF pos_scene;		stream >> pos_scene;
				QPointF	center;			stream >> center;
				qreal	rotation;		stream >> rotation;

				QGraphicsEllipseItem* load_circle = new QGraphicsEllipseItem;
				load_circle->setBrush(Qt::green);
				load_circle->setRect(rect);
				load_circle->setPos(pos_scene);
				load_circle->setTransformOriginPoint(center);
				load_circle->setRotation(rotation);

				view->get_scene()->addItem(load_circle);

			}
			else if (type_name == typeid(QGraphicsPolygonItem).name()) {

				QPolygonF	polygon;		stream >> polygon;
				QPointF		pos_scene;		stream >> pos_scene;
				QPointF		center;			stream >> center;
				qreal		rotation;		stream >> rotation;

				QGraphicsPolygonItem* load_triangle = new QGraphicsPolygonItem;
				load_triangle->setBrush(Qt::green);
				load_triangle->setPolygon(polygon);
				load_triangle->setPos(pos_scene);
				load_triangle->setTransformOriginPoint(load_triangle->mapFromScene(center));
				load_triangle->setRotation(rotation);

				view->get_scene()->addItem(load_triangle);

			}					

		}
		
		if (stream.status() != QDataStream::Ok) {
			qDebug() << "Fail Load";
		}		

	}

	file.close();

}

