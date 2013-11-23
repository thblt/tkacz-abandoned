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
#include <iostream>

#include <boost/filesystem.hpp>

#include "Tkacz.hpp"
#include "FSRepository.hpp"

namespace bfs = boost::filesystem;

namespace tkacz {

const bfs::path FSRepository::dataPath = ".tkacz",
		FSRepository::manifestFile = "manifest";

FSRepository::FSRepository(const std::string & path)
		throw (NotARepositoryException, MalformedRepositoryException,
		FileNotFoundException) {

	Tkacz::log() << "Creating FSRepository from " << path << std::endl;

	if (!bfs::exists(path))
		throw FileNotFoundException();

	if (bfs::is_regular_file(path)) {
		isZipBundle = true;
	} else if (bfs::is_directory(path)) {
		isZipBundle = false;
	} else {
		throw NotARepositoryException();
	}

}

FSRepository::~FSRepository() {
}

}
