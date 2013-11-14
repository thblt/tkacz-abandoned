/*
 * TZMainWindow.cpp
 *
 *  Created on: 6 nov. 2013
 *      Author: thblt
 */

#include <iostream>

#include "MainWindow.hpp"

#include <QtCore/QMetaObject>
#include <QtWidgets/QHBoxLayout>
namespace tzgui {

MainWindow::MainWindow() {
	tzSetupUi();
	setMenuBar(menuBar);
	QMetaObject::connectSlotsByName(this);
}

void MainWindow::on_app_about_triggered() {
	AboutDialog().exec();
}

}
