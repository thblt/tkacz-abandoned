/*
 * RootNode.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: thblt
 */

#include <cassert>
#include <set>

#include "RootNode.hpp"
#include "EntitySchema.hpp"

namespace tkacz {

RootNode::RootNode(EntitySchema &schema)
		: EntityNode(nullptr) {
	assert(schema.isRootSchema());
}

void RootNode::addTaxon(const std::initializer_list<Taxon*> taxons) {
	for (auto t : taxons) {
		t.add(this);
	}
}

void RootNode::removeTaxon(const std::initializer_list<Taxon*> taxons) {
	for (auto t : taxons) {
		t.remove(this);
	}
}

std::set<Taxon*> RootNode::getTaxons() const {
	return (std::copy(taxons));
}

void RootNode::_addTaxon(const std::initializer_list<Taxon*> taxons) {
	taxons.insert(taxons);
}

void RootNode::_removeTaxon(const std::initializer_list<Taxon*> taxons) {
	taxons.remove(taxons);
}
}
