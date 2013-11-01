#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>

#include "ui_dlgCollectionEditor.h"

int main(int argc, char* argv[]) {
	QApplication a(argc, argv);
	QDialog dlg;
	Ui_CollectionEditor ce;
	ce.setupUi(&dlg);
	dlg.show();
	a.exec();
}
