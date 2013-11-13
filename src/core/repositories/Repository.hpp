#pragma once 

#include <stdexcept>

namespace tkacz {

/**
 * @brief This exception is thrown whenever a children class of Repository
 * is unable to find the repository its supposed to open.
 * @ingroup repositories
 */
class RepositoryNotFoundException: std::runtime_error {
};
/**
 * @brief This exception is thrown whenever a children class of Repository was
 * asked to create a new repository where one already exists.
 * @ingroup repositories
 */
class RepositoryDoesExistException: std::runtime_error {
};

/**
 * @brief This exception is thrown whenever a children class of Repository was
 * asked to open a repository and was able to open something that either doesn't
 * look like a Tkacz repository or can't be accessed.
 *
 * This exception may be subclassed to distinguish between problems.
 * @ingroup repositories
 */
class MalformedRepositoryException: std::runtime_error {
};

class Repository {
public:
	Repository();
	virtual ~Repository();
};

} /* namespace tkacz */
