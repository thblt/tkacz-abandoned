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

#pragma once

#include <map>
#include <string>
#include <vector>

#include "Schema.hpp"

namespace tkacz {

class Node;

class EntitySchema: public Schema {
public:
	EntitySchema(std::string name);
	~EntitySchema();

	bool insertAttribute(std::string name, Node &value);
	bool removeAttribute(std::string name, Node &value);
	bool updateAttribute(std::string name, Node &value);

	std::vector<std::string> attributes();

	bool move(std::string name, Node &value);
	bool remove(std::string name, Node &value);

	bool isRootSchema();

	bool isStrict();
	void setStrict(bool value);

protected:
	std::map<std::string, Schema*> tplData;
};

} /* namespace tkacz */
