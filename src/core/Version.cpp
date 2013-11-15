#include <string>
#include <iostream>
#include <boost/format.hpp>

#include "Version.hpp"

namespace tkacz {

Version::Version(int major, int minor, int patch, Maturity maturity,
		int preversion, std::string name) :
		major(major), minor(minor), patch(patch), preversion(preversion), maturity(
				maturity), name(name) {
}

bool Version::operator==(Version &o) const {
	return major == o.major && minor == o.minor && patch == o.patch
			&& maturity == o.maturity;
}

bool Version::operator!=(Version &o) const {
	return !(*this == o);
}

bool Version::operator>(Version &o) const {
	if (major > o.major) return true;
	if (minor > o.minor) return true;
	if (patch > o.patch) return true;
	if (maturity > o.maturity) return true;
	return false;
}

bool Version::operator<(Version &o) const {
	if (major < o.major) return true;
	if (minor < o.minor) return true;
	if (patch < o.patch) return true;
	if (maturity < o.maturity) return true;
	return false;
}

bool Version::operator<=(Version &o) const {
	if (major <= o.major) return true;
	if (minor <= o.minor) return true;
	if (patch <= o.patch) return true;
	if (maturity <= o.maturity) return true;
	return false;
}

bool Version::operator>=(Version &o) const {
	if (major >= o.major) return true;
	if (minor >= o.minor) return true;
	if (patch >= o.patch) return true;
	if (maturity >= o.maturity) return true;
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

Version::operator std::string() const {
	std::string f;
	if (maturity == Stable)
		return boost::str(boost::format("%i.%i.%i") % major % minor % patch);
	else
		return boost::str(
				boost::format("%i.%i.%i-%s%i") % major % minor % patch % "alpha"
						% preversion);

}

//std::ostream & operator<<(std::ostream &os, Version &v) {
//	os << (std::string) v;
//	return os;
//}

std::ostream & operator<<(std::ostream &os, const Version &v) {
	os << (std::string) v;
	return os;
}
}
