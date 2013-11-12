#pragma once

#include <string>

namespace tkacz {

class Version;

class Tkacz {
public:
	/** @brief The program's version number **/
	static const Version version;

	Tkacz();
	virtual ~Tkacz();

};

}
