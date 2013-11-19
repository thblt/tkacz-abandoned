#pragma once 

/**
 * @file
 * @brief Common utilities for Tkacz
 */

#include <stdexcept>
#include <string>

#include <boost/log/sources/basic_logger.hpp>

#include "tzbuild.h"

namespace tkacz {

/* Exceptions */

/**
 * The common base class for all Tkacz exceptions
 * @ingroup exceptions
 */
class TZException: public std::runtime_error {
public:
	TZException(): std::runtime_error("") {};
};

/**
 * @ingroup exceptions
 */
class FileNotFoundException: public TZException {};
/**
 * @ingroup exceptions
 */
class FileExistsException: public TZException {};
/**
 * @ingroup exceptions
 */
class NotAFileException: public TZException {};
/**
 * @ingroup exceptions
 */
class NotADirectoryException: public TZException {};

}
