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
