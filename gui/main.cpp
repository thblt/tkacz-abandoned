#include <iostream>

#include <QtWidgets/QApplication>
#include <QtWidgets/QStyleFactory>
#include <QtWidgets/QDialog>

#include "ui_dlgCollectionEditor.h"

int main(int argc, char* argv[]) {
	std::cout << "Tkacz starting up 2.";
	QApplication app(argc, argv);
	app.setStyle(QStyleFactory::create("Fusion"));
	QDialog dlg;
	Ui_CollectionEditor ce;
	ce.setupUi(&dlg);
	dlg.show();
	app.exec();
}
