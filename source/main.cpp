#include <iostream>
#include "QT/MainWindow.h"
#include <QApplication>

int main(int argc, char** argv) {
	//std::cout << "Hello world" << std::endl;

	QApplication app(argc, argv);

	MainWindow w;
	w.setTitle("3D-Content_Creator");
	w.resize(800, 600);
	w.show();

	return app.exec();
}