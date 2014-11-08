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

/*
 * SchemaLoader.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: thblt
 */

#include <expat.h>

#include "SchemaLoader.hpp"

namespace tkacz {

void SchemaLoader::load(std::string xmlFile) {
	XML_Parser parser = XML_ParserCreate("UTF-8");
	XML_SetElementHandler(parser, startElement, endElement);
}

} /* namespace tkacz */
