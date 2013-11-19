#pragma once 

#include "tzcommon.hpp"

namespace tkacz {

class Card;
class EntityTemplate;

/**
 * @brief This exception is thrown whenever a children class of Repository was
 * asked to open a repository and got something that either doesn't look like
 * a Tkacz repository or seemed damaged.
 *
 * This exception may be subclassed if different types of problems should be reported.
 * @ingroup repositories
 * @ingroup exceptions
 */
class MalformedRepositoryException: public TZException {
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
class NotARepositoryException: public TZException  {
};

/**
 * @brief A base interface for Tkacz repositories.
 * @ingroup repositories
 */
class Repository {
};
}
