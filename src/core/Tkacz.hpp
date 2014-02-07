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

#include <Version.hpp>  // Better not to forward declaration to make users of Tkacz.hpp
						// aware of the stream operators

namespace tkacz {

/**
 * @brief The main application class.
 * @ingroup core
 */
class Tkacz {
public:
	/** @brief The program's version number **/
	static const Version version;
	static Tkacz* getInstance();

	// Logging methods
	static std::ostream& log();
	static std::ostream& log(std::string msg);

protected:
	Tkacz();
	~Tkacz();

	static Tkacz *instance;
};

std::ostream& tzlog() { return (Tkacz::log()); }
std::ostream& tzlog(std::string msg) { return (Tkacz::log(msg)); }

}
