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

#include "Repository.hpp"

namespace boost {
namespace filesystem {
class path;
}
}

namespace tkacz {

/**
 * @brief Accesses a Tkacz repository stored as a directory.
 * @ingroup repositories
 */
class FSRepository: public Repository {

public:
	/**
	 * @param path The path of the repository to open.
	 */
	FSRepository(const std::string & path) throw (NotARepositoryException,
			MalformedRepositoryException, FileNotFoundException);

	~FSRepository();

	/**
	 * Creates a new repository on filesystem. Please notice that this will
	 * overwrite any existing contents.
	 *
	 * @param path Where to create the repository.
	 * @param zipped If true, creates a zipped bundle instead of a directory.
	 * @return A FSRepository object representing the newly created repository.
	 *
	 */
	static FSRepository & initialize(const std::string &path,
			const bool zipped = false) throw (FileExistsException);

protected:
	/**
	 * Whether this repository was loaded from a zipped bundle file.
	 */
	bool isZipBundle = false;
	/**
	 * The path to the data directory
	 */
	static const boost::filesystem::path dataPath,
	/**
	 * The path to the manifest file
	 */
	manifestFile;
};

}
