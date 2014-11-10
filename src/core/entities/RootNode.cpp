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

#include <cassert>
#include <set>

#include "Taxon.hpp"
#include "RootNode.hpp"
#include "EntitySchema.hpp"

namespace tkacz {

RootNode::RootNode(EntitySchema &schema)
		: EntityNode(nullptr) {
	assert(schema.isRootSchema());
}

void RootNode::addTaxon(const std::initializer_list<Taxon*> taxons) {
	for (auto t : taxons) {
		t->add(this);
	}
}

void RootNode::removeTaxon(const std::initializer_list<Taxon*> taxons) {
	for (auto t : taxons) {
		t->remove(this);
	}
}

std::set<Taxon*> RootNode::getTaxons() const {
	return (taxons);
}

void RootNode::_addTaxon(const std::initializer_list<Taxon*> taxons) {
	for (auto t : taxons)
		this->taxons.insert(t);
}

void RootNode::_removeTaxon(const std::initializer_list<Taxon*> taxons) {
	for (auto t : taxons)
		this->taxons.erase(t);
}
}
