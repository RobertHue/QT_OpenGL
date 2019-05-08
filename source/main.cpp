#include <iostream>
#include "graphics/Window.h"
#include <QApplication>

int main(int argc, char** argv) {
	//std::cout << "Hello world" << std::endl;

	QApplication app(argc, argv);

	Window mainWindow;
	mainWindow.setTitle("3D-Content_Creator");
	mainWindow.resize(800, 600);
	mainWindow.show();

	return app.exec();
}