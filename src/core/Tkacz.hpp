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

namespace tkacz {

class Version;

enum class LogLevel : int {
	_NONE = 0,
	DEBUG = 10,
	FINE = 20,
	INFO = 30,
	MESSAGE = 40,
	WARNING = 50,
	SEVERE = 60,
	FATAL = 70,
	_ALL = 2048
};

/**
 * @brief The main application class.
 * @ingroup core
 */
class Tkacz {
public:
	/** @brief The program's version number **/
	static const Version version;
	static Tkacz* getInstance();

	static std::ostream& log(LogLevel lvl=LogLevel::MESSAGE, std::string msg="");

protected:
	Tkacz();
	~Tkacz();

	static Tkacz *instance;
};


// Shortcuts to logging functions //
std::ostream& log(LogLevel lvl=LogLevel::MESSAGE, std::string msg="") { return (Tkacz::log(lvl, msg)); }

std::ostream& debug_msg(std::string msg="") { return (Tkacz::log(LogLevel::DEBUG, msg)); }
std::ostream& fine(std::string msg="")      { return (Tkacz::log(LogLevel::FINE, msg)); }
std::ostream& info(std::string msg="")      { return (Tkacz::log(LogLevel::INFO, msg)); }
std::ostream& say(std::string msg="")       { return (Tkacz::log(LogLevel::MESSAGE, msg)); }
std::ostream& warn(std::string msg="")      { return (Tkacz::log(LogLevel::WARNING, msg)); }
std::ostream& severe(std::string msg="")    { return (Tkacz::log(LogLevel::SEVERE, msg)); }
std::ostream& fatal(std::string msg="")     { return (Tkacz::log(LogLevel::FATAL, msg)); }
}