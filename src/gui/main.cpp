/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2014 Thibault Polge. All rights reserved.
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
#include <string>

#include "Tkacz.hpp"
#include "MainWindow.hpp"
#include "Repository.hpp"

using namespace tzgui;
using namespace tkacz;

int main(int argc, char* argv[]) {

	TZ_TRACE << "Tkacz " << Tkacz::version << " “" << Tkacz::version.name << "“"
			<< std::endl;

	QApplication app(argc, argv);
	app.setAttribute(Qt::AA_UseHighDpiPixmaps);

	MainWindow mw;
	mw.showMaximized();

	TZ_FINE << "Initializing core";
	// Tkacz::getInstance(); // Forces core initialization

	TZ_FINE << "Running application";
	return (app.exec());
	return 0;
}