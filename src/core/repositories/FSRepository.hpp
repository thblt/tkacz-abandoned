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
	 * @param create Whether or no
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
