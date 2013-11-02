#include <iostream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QDialog>
#include <QtWidgets/QSplashScreen>

#include "ui_dlgCollectionEditor.h"

int main(int argc, char* argv[]) {
	QApplication app(argc, argv);

	QPixmap pixmap("/Users/thblt/Temporaire/tkacz.png");
	QSplashScreen splash(pixmap);
	splash.show();
	app.processEvents();
	QDialog dlg;
	Ui_CollectionEditor().setupUi(&dlg);
	dlg.show();
	splash.finish(&dlg);
	app.exec();
}
