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

#pragma once 

#include <string>

#include <expat.h>

namespace tkacz {

class SchemaLoader {
public:
	/** @brief Loads a schema.
	 *
	 * WARNING This class is pure static.
	 *
	 * @param xmlFile The root file to parse. Use Xincludes to add extra files.
	 */
	static void load(std::string xmlFile);

	static void startElement(void *data, const char *element, const char **attribute);
	static void endElement(void *data, const char *el);

protected:
	std::string xmlFile;

private:
	SchemaLoader();
};

} /* namespace tkacz */
