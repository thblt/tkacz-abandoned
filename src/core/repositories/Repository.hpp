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

#include <git2/types.h>

#include "Exception.hpp"
#include "Repository.hpp"

namespace boost {
	namespace filesystem {
		class path;
	}
};
namespace bfs = boost::filesystem;

namespace tkacz {

/**
 * @brief This exception is thrown whenever a children class of Repository was
 * asked to open a repository and got something that either doesn't look like
 * a Tkacz repository or seemed damaged.
 *
 * This exception may be subclassed if different types of problems should be reported.
 * @ingroup repositories
 * @ingroup exceptions
 */
class MalformedRepositoryException: public Exception {
};

/**
 * @brief This exception is thrown whenever a children class of Repository was
 * asked to open something that definitely doesn't look like a Tkacz repository.
 * This exception should be preferred over MalformedRepositoryException when there
 * doesn't seem to be any way to get any data from the given location.
 *
 * This exception may be subclassed if different types of problems should be reported.
 * @ingroup repositories
 * @ingroup exceptions
 */
class NotARepositoryException: public Exception {
};

/**
 * @brief A base interface for Tkacz repositories.
 * @ingroup repositories
 */

/**
 * @brief Accesses a Tkacz repository stored as a directory.
 * @ingroup repositories
 */
class Repository{

public:
	/**
	 * @param path The path of the repository to open.
	 */
	Repository(const boost::filesystem::path & path) throw (NotARepositoryException,
			MalformedRepositoryException, FileNotFoundException);

	~Repository();
	
	/**
	 * Creates a new repository on filesystem. Please notice that this will
	 * overwrite any existing contents.
	 *
	 * @param path Where to create the repository.
	 * @param zipped If true, creates a zipped bundle instead of a directory.
	 * @return A Repository object representing the newly created repository.
	 */
	 static Repository & initialize(const bfs::path & path = ".", bool mkdir = true, bool mk_interm = false, bool lock = false) throw (Exception);

	/** 
	 * Locks this repository against concurrent access. 
	 * 
	 * @param timeout If lock is enabled, wait timeout ms before giving up.
	 * @param retry_interval Time to wait before trying again.
	 * @return true if a lock has been acquired before timeout, false either.
	*/
	bool lock_acquire(unsigned int timeout=0, unsigned int retry_interval=50);
	
	/** 
	 * Releases this repository's lock.
	 * 
	 * @param force If true, release the repository even if owned by a different process.
	 * @return true if this repository was locked by the current process and released, false either. 
	 * Notice that returning false doesn't mean the repository is unlocked, since it may have been owned
	 * by a different process.
	*/
	bool lock_release(bool force=false);

protected:
	/**
	 * The path to the data directory
	 */
	static const boost::filesystem::path dataPath,
	/**
	 * The path to the manifest file
	 */
	manifestFile;
	/**
	 * The GIT repository
	 */
	git_repository *git_repo;
};

}
