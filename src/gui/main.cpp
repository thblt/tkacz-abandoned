#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

#include "TZMainWindow.h"

using namespace tzgui;

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	MainWindow mw;
	mw.show();
	app.exec();
}
