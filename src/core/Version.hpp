#pragma once

#include <string>

namespace tkacz {

/**
 * @brief A simple class for storing and comparing version numbers.
 *
 * Tkacz uses <a href="http://semver.org/">semantic versioning</a>. Please notice
 * that semantic versioning does not guarantee backwards compatibility for major==0.
 * If major==0, backwards compatibility is guaranteed within the same minor version, eg:
 * 0.4.12 is compatible with 0.4.43 but neither with 0.3.x or 0.5.x.
 *
 * @ingroup core
 */
class Version {

public:
	enum Maturity {
		Alpha, Beta, Stable
	};

	/** @brief Major version number */
	const int major,
	/** @brief Minor version number */
	minor,
	/** @brief Patch number */
	patch;
	/** Version maturity **/
	const Maturity maturity;
	/** Version codename */
	const std::string name,
	/** Full version number as as string */
	signature;

	/**
	 * @brief Creates a new AppVersion object.
	 *
	 * @param major The major version number
	 * @param minor The minor version number
	 * @param patch The patch number.
	 * @param maturity The maturity level.
	 * @param name A code name for this version.
	 */
	Version(int major, int minor = 0, int patch = 0, Maturity maturity = Stable,
			std::string name = "");

	bool operator==(Version &o) const;
	bool operator!=(Version &o) const;
	bool operator>(Version &o) const;
	bool operator<(Version &o) const;
	bool operator<=(Version &o) const;
	bool operator>=(Version &o) const;

	bool isCompatible(Version &o) const;
};
}
