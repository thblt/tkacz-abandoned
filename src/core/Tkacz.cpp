/*
 * tkacz.cpp
 *
 *  Created on: 31 oct. 2013
 *      Author: tehboii
 */

#if __cplusplus <= 201100L
  #warning Tkacz requires a C++11 compliant compiler.
#endif

#include "TZBuildConfig.h"
#include "TZAppVersion.h"
#include "tkacz.h"

namespace tkacz {

const AppVersion Tkacz::version = { TZ_VERSION_MAJOR, TZ_VERSION_MINOR,
TZ_VERSION_RELEASE, AppVersion::Maturity::ALPHA, "Boyle" };

Tkacz::Tkacz() {
	// TODO Auto-generated constructor stub
}

Tkacz::~Tkacz() {
	// TODO Auto-generated destructor stub
}

}
