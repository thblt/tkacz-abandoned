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

#include "Schema.hpp"

namespace tkacz {

/**
 * A Primitive holds a simple value, such as an integer, a string or a float.
 */
template<typename T>
class PrimitiveTemplate: public Schema {
public:
	virtual T& getValue();

protected:
	T value;

	PrimitiveTemplate();
	virtual ~PrimitiveTemplate();
};

}
