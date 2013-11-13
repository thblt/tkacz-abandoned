#if __cplusplus < 201103L
  #error Tkacz requires a C++11 compliant compiler
#endif

#include "TZGlobals.h"
#include "Version.hpp"
#include "Tkacz.hpp"

namespace tkacz {

const Version Tkacz::version = { TZ_VERSION_MAJOR, TZ_VERSION_MINOR,
TZ_VERSION_PATCH, Version::Maturity::TZ_VERSION_MATURITY, TZ_VERSION_NAME };

Tkacz::Tkacz() {
	// TODO Auto-generated constructor stub
}

Tkacz::~Tkacz() {
	// TODO Auto-generated destructor stub
}

}
