#include <iostream>

#include <QtWidgets/QSplashScreen>

#include "Tkacz.hpp"

#include "MainWindow.hpp"

using namespace tzgui;

int main(int argc, char* argv[]) {
	std::cout << "Tkacz " << tkacz::Tkacz::version << " “"
			<< tkacz::Tkacz::version.name << "“" << std::endl;

	QApplication app(argc, argv);

	app.setAttribute(Qt::AA_UseHighDpiPixmaps);
	app.setAttribute(Qt::AA_DontUseNativeMenuBar);

	QPixmap pixmap(":/tkacz/splash");
	QSplashScreen splash(pixmap);
	splash.show();

	MainWindow mw;
	mw.showMaximized();

	splash.finish(&mw);

	return app.exec();
}
