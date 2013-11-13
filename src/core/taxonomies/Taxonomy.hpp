#pragma once

#include <string>
#include <vector>
#include "Taxon.hpp"

using namespace std;

namespace tkacz {

class Taxonomy: public Taxon {
public:
	const bool root = true;
	Taxonomy(string name, const vector<Taxon*>& children = vector<Taxon*>(0)) :
			Taxon(name, NULL, children) {
	}
	;

};

}
