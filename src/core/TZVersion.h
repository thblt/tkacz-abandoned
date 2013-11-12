#pragma once

#include <string>

namespace tkacz {

/**
 * @brief A simple class for storing and comparing version numbers.
 * @ingroup core
 */
class Version {

public:
	enum Maturity {
		Alpha, Beta, Stable
	};

	const int major, minor, revision;
	const Maturity maturity;
	const std::string name;

	/**
	 * @brief Creates a new AppVersion object.
	 *
	 * @param major The major version number
	 * @param minor The minor version number
	 * @param revision The revision number.
	 * @param maturity The maturity level.
	 * @param name A code name for this version.
	 */
	Version(int major, int minor=0, int revision=0, Maturity maturity=Stable,
			std::string name = "") :
			major(major), minor(minor), revision(revision), maturity(maturity), name(
					name) {
	}

//	std::string signature() {
//		return "%s %i.%i.%i %s";
//	}

	bool operator==(Version &o) {
		return major == o.major && minor == o.minor && revision == o.revision
				&& maturity == o.maturity;
	}

//	bool operator!=(AppVersion &o) {
//		return this == o;
//	}

	bool operator>(Version &o) {
		if (major > o.major)
			return true;
		if (minor > o.minor)
			return true;
		if (revision > o.revision)
			return true;
		if (maturity > o.maturity)
			return true;
		return false;
	}

	bool operator<(Version &o) {
		if (major < o.major)
			return true;
		if (minor < o.minor)
			return true;
		if (revision < o.revision)
			return true;
		if (maturity < o.maturity)
			return true;
		return false;
	}

	bool operator<=(Version &o) {
		if (major <= o.major)
			return true;
		if (minor <= o.minor)
			return true;
		if (revision <= o.revision)
			return true;
		if (maturity <= o.maturity)
			return true;
		return false;
	}

	bool operator>=(Version &o) {
		if (major >= o.major)
			return true;
		if (minor >= o.minor)
			return true;
		if (revision >= o.revision)
			return true;
		if (maturity >= o.maturity)
			return true;
		return false;
	}
};
}
;
