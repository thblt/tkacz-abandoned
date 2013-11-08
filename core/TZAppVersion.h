#pragma once

#include <string>

/**
 * @addtogroup core
 * @{
 */

namespace tkacz {

class AppVersion {


public:
	enum Maturity {
		Alpha, Beta, Stable
	};

	const int major, minor, revision;
	const Maturity maturity;

	AppVersion(int major, int minor, int revision, Maturity maturity) :
			major(major), minor(minor), revision(revision), maturity(maturity) {
	}

//	std::string signature() {
//		return "%s %i.%i.%i %s";
//	}

	bool operator==(AppVersion &o) {
		return major == o.major && minor == o.minor && revision == o.revision && maturity == o.maturity;
	}

//	bool operator!=(AppVersion &o) {
//		return this == o;
//	}

	bool operator>(AppVersion &o) {
		if ( major > o.major ) return true;
		if ( minor > o.minor ) return true;
		if ( revision > o.revision ) return true;
		if ( maturity > o.maturity ) return true;
		return false;
	}

	bool operator<(AppVersion &o) {
		if ( major < o.major ) return true;
		if ( minor < o.minor ) return true;
		if ( revision < o.revision ) return true;
		if ( maturity < o.maturity ) return true;
		return false;
	}

	bool operator<=(AppVersion &o) {
		if ( major <= o.major ) return true;
		if ( minor <= o.minor ) return true;
		if ( revision <= o.revision ) return true;
		if ( maturity <= o.maturity ) return true;
		return false;
	}

	bool operator>=(AppVersion &o) {
		if ( major >= o.major ) return true;
		if ( minor >= o.minor ) return true;
		if ( revision >= o.revision ) return true;
		if ( maturity >= o.maturity ) return true;
		return false;
	}
};
}
;
