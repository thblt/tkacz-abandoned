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

#include <boost/python.hpp>
#include <boost/python/module_init.hpp>



#include "Tkacz.hpp"
#include "MainWindow.hpp"
#include "FSRepository.hpp"

using namespace tzgui;
using namespace tkacz;
using namespace boost::python;

void greet() {
	// Retrieve the main module.
	object main = import("__main__");

	// Retrieve the main module's namespace
	object global(main.attr("__dict__"));

	// Define greet function in Python.
	object result = exec("def greet():\n"
			"\timport sys \n"
			"\tprint(sys.version_info)\n"
			"\treturn 'Hello from Python!' \n", global, global);

	// Create a reference to it.
	object greet = global["greet"];

	// Call it.
	std::string message = extract < std::string > (greet());
	std::cout << message << std::endl;
}

int main(int argc, char* argv[]) {

	Py_Initialize();

	greet();

	tzlog() << "Tkacz " << Tkacz::version << " “" << Tkacz::version.name << "“"
			<< std::endl;

	QApplication app(argc, argv);
	app.setAttribute(Qt::AA_UseHighDpiPixmaps);

	MainWindow mw;
	mw.showMaximized();

	tzlog("Initializing core");
	Tkacz::getInstance(); // Forces core initialization

	Tkacz::log("Running application");
	return (app.exec());
//	return 0;
}
