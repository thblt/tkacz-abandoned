/*
 * TZTaxon.h
 *
 *  Created on: 7 nov. 2013
 *      Author: thblt
 */

#pragma once

#include <string>
#include <vector>
#include "TZCard.h"

namespace tkacz {

class Taxon {
public:
	Taxon& getParent();
	std::vector<Card*>& getContents();
	Taxon(std::string name);
	Taxon(std::string name, Taxon* parent, const std::vector<Taxon*>& children);
	virtual ~Taxon();
	const bool root = false;

protected:
	std::string name;
	Taxon &parent;
	std::vector<Taxon*> children;
	std::vector<Card*> contents;
};

} /* namespace tkacz */
