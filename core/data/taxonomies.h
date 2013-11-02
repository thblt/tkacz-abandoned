#pragma once

#include <string>
#include <vector>
#include "types.h"

using namespace std;

namespace tkacz {

class TaxonomyRule {

};

class Taxon {
public:
	Taxon& getParent();
	vector<Card*>& getContents();
	Taxon(string name);
	Taxon(string name, Taxon* parent, const vector<Taxon*>& children);
	virtual ~Taxon();
	const bool root = false;

protected:
	string name;
	Taxon &parent;
	vector<Taxon*> children;
	vector<Card*> contents;
};

class Taxonomy: public Taxon {
public:
	const bool root = true;
	Taxonomy(string name, const vector<Taxon*>& children = vector<Taxon*>(0)) :
			Taxon(name, NULL, children) {};

};

}
