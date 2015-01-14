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

#include <exception>

#define TZ_BASIC_EXCEPTION(NAME, PARENT) class NAME : public PARENT { public: NAME(const char * what = #NAME) : PARENT(wtf) {} };

namespace tkacz {
	class Exception : public std::exception {
    public:
		const char * wtf;

        Exception(const char * wtf) : wtf (wtf) {};
	};

    /*************************
     * Filesystem exceptions *
     *************************/
    TZ_BASIC_EXCEPTION ( FSException, 					Exception );
    TZ_BASIC_EXCEPTION ( NotADirectoryException, 		FSException);
    TZ_BASIC_EXCEPTION ( NotAFileException, 			FSException);
    TZ_BASIC_EXCEPTION ( NotEmptyException, 			FSException);
    TZ_BASIC_EXCEPTION ( NotWritableException, 			FSException);
    TZ_BASIC_EXCEPTION ( NotReadableException, 			FSException);
    TZ_BASIC_EXCEPTION ( PathDoesNotExistException, 	FSException);

}