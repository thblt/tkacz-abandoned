/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2015 Thibault Polge. All rights reserved.
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

#include <boost/log/trivial.hpp>

#include "tzbuild.h"

using namespace std;

namespace tkacz {
	class Version;
	
    class Tkacz {

    public:

        enum class LogLevel : int {
            _NONE   =   0,
            TRACE   =   10,
            DEBUG   =   20,
            INFO    =   30,
            WARNING =   50,
            SEVERE  =   60,
            FATAL   =   70,
            _ALL    =   1024
        };

        static const Version version;

        static void init();
		static void finalize();

	private:
		
		Tkacz();
				       
    };
}

#define TZ_LOG(msg) std::cout << msg << std::endl;
#define TZ_TRACE(msg) std::cout << msg << std::endl;
#define TZ_FINE(msg) std::cout << msg << std::endl;
#define TZ_WARN(msg) std::cout << msg << std::endl;