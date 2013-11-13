#pragma once

namespace tkacz {

class Version;

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
