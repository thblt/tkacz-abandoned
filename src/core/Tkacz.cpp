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

#include "Tkacz.hpp"

#include <iostream>

#include "Platform.hpp"
#include "tzbuild.h"
//#include "Version.hpp"

namespace tkacz {

const Version Tkacz::version = { TZ_VERSION_MAJOR, TZ_VERSION_MINOR,
TZ_VERSION_PATCH, Version::Maturity::TZ_VERSION_MATURITY, TZ_VERSION_PREVERSION,
TZ_VERSION_NAME };

Tkacz::Tkacz() {
	Platform::init();
	tzlog() << Platform::getResourcePath("Tkacz.icns") << std::endl;
	//SchemaLoader(Platform::getCanonicalResourcePath("schema/base.xml")).run();
}

void Tkacz::test() {
}

Tkacz* Tkacz::getInstance() {
	if (instance == nullptr) {
		instance = new Tkacz();
	}
	return (instance);
}

std::ostream& Tkacz::log() {
	return (std::cout << "[log] ");
}

std::ostream& Tkacz::log(const std::string msg) {
	return (log() << msg << std::endl);
}

Tkacz::~Tkacz() {
}

Tkacz* Tkacz::instance = nullptr;

}
