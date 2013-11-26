/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2013 Thibault Polge. All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                [/licblock] */

#include <iostream>

#include "MainWindow.hpp"

#include <QtCore/QMetaObject>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QVBoxLayout>

#include "ViewPerspective.hpp"

namespace tzgui {

MainWindow::MainWindow() {
	tzSetupUi(this);

	setMenuBar(mainMenu);

	// Build main toolbar
	toolBar = new QToolBar();
	toolBar->setMovable(false);
	this->addToolBar(toolBar);
	toolBar->addAction(actionPageCreatePopup);
	toolBar->addAction(actionCollectionCreateFromrules);
	toolBar->addWidget(addressBar= new QLineEdit());
	toolBar->addAction(actionWindowFullscreen);

	// Init views
	setCentralWidget(container = new QStackedWidget());
	viewPersp = new ViewPerspective();
	container->addWidget(viewPersp);
	container->setCurrentIndex(0);

	QMetaObject::connectSlotsByName(this);

}

void MainWindow::on_app_about_triggered() {
	AboutDialog().exec();
}

}
