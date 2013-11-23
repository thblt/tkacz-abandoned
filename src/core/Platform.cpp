#include "Platform.hpp"
#include "Tkacz.hpp"

#if defined(__APPLE__) && defined(__MACH__)

/*
 * Adapted from:
 * http://www.experimentgarden.com/2009/06/how-to-load-resource-from-your.html
 * @FIXME License unknown
 */

#include "CoreFoundation/CFBundle.h"

namespace tkacz {

	CFBundleRef Platform::mainBundle = CFBundleGetMainBundle();

	void Platform::init() {
		// Nothing to do.
	}

	const char* Platform::getResourcePath(const char *file)
	{
		CFURLRef resourceURL;
		// Look for the resource in the main bundle by name and type.
		resourceURL = CFBundleCopyResourceURL(mainBundle,
				CFStringCreateWithCString(NULL, file,
						kCFStringEncodingASCII),
				NULL, NULL);

		if (!resourceURL) {
			Tkacz::log("Missing resource ");
			Tkacz::log(std::string(file));
			Tkacz::log("Missing resource ");
			return nullptr;
		}

		char *fileurl = new char[200];

		if (!CFURLGetFileSystemRepresentation(resourceURL, true, (UInt8*) fileurl,
						200))

		{
			throw "Failed to turn a bundle resource URL into a filesystem path representation!";
		} else {
			return (fileurl);
		}
	}

#define TZ_RES(PATH) absoluteBundleResourcePath(#PATH)

} /* namespace */

#endif
