#include <iostream>
#include "Tkacz.hpp"
#include "MainWindow.hpp"

#include "FSRepository.hpp"

using namespace tzgui;

int main(int argc, char* argv[]) {
	std::cout << "Tkacz " << tkacz::Tkacz::version << " “"
			<< tkacz::Tkacz::version.name << "“" << std::endl;

	QApplication app(argc, argv);

	tkacz::FSRepository repo { "/Users/thblt/Temoraire/repo.tkacz" };

	app.setAttribute(Qt::AA_UseHighDpiPixmaps);

	MainWindow mw;
	mw.showMaximized();

//	return app.exec();
}
