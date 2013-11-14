#include <iostream>
//#include <string>

#include "MainWindow.hpp"

using namespace tzgui;

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MainWindow mw;
	mw.showMaximized();
	return app.exec();
}
