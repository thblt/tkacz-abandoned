#include <string>
#include <iostream>
#include <boost/format.hpp>

#include "Version.hpp"

namespace tkacz {

Version::Version(int major, int minor, int patch, Maturity maturity,
		std::string name) :
		major(major), minor(minor), patch(patch), maturity(maturity), name(name) {
	std::cout << boost::format("%i.%i.%i") % major % minor % patch;
}

bool Version::operator==(Version &o) const {
	return major == o.major && minor == o.minor && patch == o.patch
			&& maturity == o.maturity;
}

bool Version::operator!=(Version &o) const {
	return !(*this == o);
}

bool Version::operator>(Version &o) const {
	if (major > o.major)
		return true;
	if (minor > o.minor)
		return true;
	if (patch > o.patch)
		return true;
	if (maturity > o.maturity)
		return true;
	return false;
}

bool Version::operator<(Version &o) const {
	if (major < o.major)
		return true;
	if (minor < o.minor)
		return true;
	if (patch < o.patch)
		return true;
	if (maturity < o.maturity)
		return true;
	return false;
}

bool Version::operator<=(Version &o) const {
	if (major <= o.major)
		return true;
	if (minor <= o.minor)
		return true;
	if (patch <= o.patch)
		return true;
	if (maturity <= o.maturity)
		return true;
	return false;
}

bool Version::operator>=(Version &o) const {
	if (major >= o.major)
		return true;
	if (minor >= o.minor)
		return true;
	if (patch >= o.patch)
		return true;
	if (maturity >= o.maturity)
		return true;
	return false;
}

/**
 * @param o The Version object to compare with.
 * @return True if this Version object is compatible with o.
 */
bool Version::isCompatible(Version &o) const {
	if (not major)
		return o.major == 0 && minor == o.minor;
	else
		return major == o.major;
}

}
