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


#include <unistd.h>

#include <boost/filesystem.hpp>
#include <git2/repository.h>

#include "Tkacz.hpp"
#include "Repository.hpp"

namespace bfs = boost::filesystem;

namespace tkacz {

const bfs::path Repository::dataPath = ".tkacz",
		Repository::manifestFile = "manifest";

Repository::Repository(const bfs::path & path) throw (NotARepositoryException,
		MalformedRepositoryException, FileNotFoundException) {

	info() << "Attempting to open Repository from " << path << std::endl;

	if (!bfs::exists(path))
		throw FileNotFoundException();

	if (!bfs::is_directory(path)) {
		throw NotARepositoryException();
	}
}

Repository & Repository::initialize (const bfs::path & path, bool mkdir, bool mk_interm, bool lock) throw (Exception) {

	if (!bfs::exists(path)) {
		bfs::create_directory(path);
	}

}

Repository::~Repository() {
}

}
