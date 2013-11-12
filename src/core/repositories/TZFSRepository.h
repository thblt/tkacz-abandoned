#pragma once 

#include <string>
#include <exception>

#include <boost/filesystem.hpp>

namespace tkacz {

/**
 * @brief Accesses a Tkacz repository stored as a filesystem repository.
 * @ingroup repositories
 */
class FSRepository {
public:
	/**
	 * @param path
	 * @param create
	 *
	 * @throws runtime_error If !create, then a runtime_error is thrown
	 */
	FSRepository(std::string path, bool create=false) throw(std::runtime_error);
	virtual ~FSRepository();

protected:
	static const std::string
	/**
	 * The path to the data directory
	 */
	dataPath[],
	/**
	 * The path to the manifest file
	 */
	manifestPath[];

};

}
