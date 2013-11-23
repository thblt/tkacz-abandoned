#pragma once

#if defined(__APPLE__) && defined(__MACH__)
#include "CoreFoundation/CFBundle.h"
#endif

namespace tkacz {

class Platform {
public:
	static void init();
	static const char* getResourcePath(const char *file);

private:
	Platform();
#if defined(__APPLE__) && defined(__MACH__)
	static CFBundleRef mainBundle;
#endif

};

}
