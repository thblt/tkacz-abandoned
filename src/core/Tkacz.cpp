#if __cplusplus <= 201100L
  #warning Tkacz requires a C++11 compliant compiler.
#endif

#include "TZBuildConfig.h"
#include "TZVersion.h"
#include "tkacz.h"

namespace tkacz {

const Version Tkacz::version = { TZ_VERSION_MAJOR, TZ_VERSION_MINOR,
TZ_VERSION_RELEASE, Version::Maturity::TZ_VERSION_MATURITY, "Boyle" };

Tkacz::Tkacz() {
	// TODO Auto-generated constructor stub
}

Tkacz::~Tkacz() {
	// TODO Auto-generated destructor stub
}

}
