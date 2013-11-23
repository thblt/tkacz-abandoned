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

#pragma once

#include <string>
#include <map>

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
		Alpha, Beta, RC, Stable
	};

	/** @brief Major version number */
	const int major,
	/** @brief Minor version number */
	minor,
	/** @brief Patch number */
	patch,
	/** @brief preversion (as in x.y.z-beta{preversion}. This is not taken into account when comparing. */
	preversion;
	/** @brief Version maturity **/
	const Maturity maturity;
	/** @brief Version codename */
	const std::string name,
	/** @brief Full version number as string */
	signature;

	/**
	 * @brief Creates a new AppVersion object.
	 *
	 * @param major The major version number
	 * @param minor The minor version number
	 * @param patch The patch number.
	 * @param maturity The maturity level.
	 * @param preversion The pre-version number (as in alpha1). Unused if maturity = Stable.
	 * @param name A code name for this version.
	 */
	Version(const int major, const int minor = 0, const int patch = 0, const Maturity maturity = Stable,
			const int preversion=0, const std::string name = "");

	bool operator==(Version &o) const;
	bool operator!=(Version &o) const;
	bool operator>(Version &o) const;
	bool operator<(Version &o) const;
	bool operator<=(Version &o) const;
	bool operator>=(Version &o) const;

	bool isCompatible(Version &o) const;

	operator std::string() const;
};

//std::ostream & operator<<(std::ostream &os, Version &v);
std::ostream & operator<<(std::ostream &os, const Version &v);
}
