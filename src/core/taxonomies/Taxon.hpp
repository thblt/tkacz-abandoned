/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2014 Thibault Polge. All rights reserved.
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

#include <initializer_list>
#include <string>
#include <set>

namespace tkacz {

class RootNode;

class Taxon {
public:
	Taxon& getParent();
	std::set<RootNode*>& getContents() const;

	Taxon(std::string name);
	Taxon(std::string name, Taxon* parent, const std::initializer_list<Taxon*> children);
	virtual ~Taxon();
	const bool root = false;

	void add(RootNode * a);
	void remove(RootNode * a);

	int size() const;

protected:
	std::string name;
	Taxon &parent;
	std::set<Taxon*> children;
	std::set<RootNode*> contents;
};

} /* namespace tkacz */
