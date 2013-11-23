#pragma once 

#include <stdexcept>

namespace tkacz {

/**
 * The common base class for all Tkacz exceptions
 * @ingroup exceptions
 */
class Exception: public std::runtime_error {
public:
	Exception()
			: std::runtime_error("") {
	}
	;
};

/**
 * @ingroup exceptions
 */
class FileNotFoundException: public Exception {
};

/**
 * @ingroup exceptions
 */
class FileExistsException: public Exception {
};

/**
 * @ingroup exceptions
 */
class NotAFileException: public Exception {
};

/**
 * @ingroup exceptions
 */
class NotADirectoryException: public Exception {
};

}
