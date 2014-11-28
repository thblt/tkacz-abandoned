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

#include <iostream>

#include <boost/filesystem.hpp>
#include <git2/repository.h>

#include "Exception.hpp"
#include "Repository.hpp"

namespace bfs = boost::filesystem;

namespace tkacz {

    Repository::Repository(const bfs::path & path) {

    }

    Repository Repository::initialize (const bfs::path & path, bool force) {

        if (!bfs::exists(path))
            throw PathDoesNotExistException();

        if (!bfs::is_directory(path)) {
            throw NotADirectoryException();
        }

        if (!bfs::is_empty(path)) {
            throw NotEmptyException();
        }

        std::cout << bfs::status(path).permissions();
        
        return { path };
        
    }
    
}
