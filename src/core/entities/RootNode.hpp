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

#include <set>
#include <vector>
#include <initializer_list>
#include <iostream>

#include "EntityNode.hpp"

namespace tkacz {

class Taxon;

class EntitySchema;

class RootNode: public tkacz::EntityNode {

	friend class Taxon;

public:
	void addTaxon(const std::initializer_list<Taxon*> taxons);
	void removeTaxon(const std::initializer_list<Taxon*> taxons);
	std::set<Taxon*> getTaxons() const;

	RootNode(EntitySchema &schema);

protected:
	std::set<Taxon*> taxons;
	void _addTaxon(const std::initializer_list<Taxon*> t);
	void _removeTaxon(const std::initializer_list<Taxon*> t);

	std::vector<Taxon*> x;

};

} /* namespace tkacz */
