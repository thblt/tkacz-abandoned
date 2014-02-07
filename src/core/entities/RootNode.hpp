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
