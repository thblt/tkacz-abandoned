/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2013 Thibault Polge. All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                [/licblock] */

#include <string>
#include <iostream>
#include <boost/format.hpp>

#include "Version.hpp"

namespace tkacz {

Version::Version(int major, int minor, int patch, Maturity maturity,
		int preversion, std::string name)
		: major(major), minor(minor), patch(patch), preversion(preversion), maturity(
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

Version::operator std::string() const {
	std::string mat;
	switch (maturity) {
	case Stable:
		return boost::str(boost::format("%i.%i.%i") % major % minor % patch);
	case Alpha:
		mat = "alpha";
		break;
	case Beta:
		mat = "beta";
		break;
	case RC:
		mat = "rc";
		break;
	}
	return boost::str(
			boost::format("%i.%i.%i-%s%i") % major % minor % patch % mat
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
