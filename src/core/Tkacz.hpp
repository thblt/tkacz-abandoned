#pragma once

#include <Version.hpp>  // Better not to forward declaration to make users of Tkacz.hpp
						// aware of the stream operators

namespace tkacz {

/**
 * @brief The main application class.
 * @ingroup core
 */
class Tkacz {
public:
	/** @brief The program's version number **/
	static const Version version;

	Tkacz();
	virtual ~Tkacz();

};

}
