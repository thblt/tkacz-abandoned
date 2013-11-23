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

#include <string>

namespace tkacz {

class Node;

/**
 * @brief A Schema is a constraint for a Node.
 *
 * Schema itself is a purely virtual class. There is a one-to-one relationship between
 * the Template class hierarchy and the Node hierarchy, ie, every ValueNode uses a
 * ValueSchema object, every EntityNode uses an EntityTemplate, and so on.
 *
 * @ingroup schemas
 */
class Schema {
public:
	const std::string name;

	/** @brief Builds a new Node with this Schema **/
	template<typename args> Node make(args...);

	Schema(std::string name) : name(name) {};
	virtual ~Schema();
};

}
