#pragma once

#include <initializer_list>
#include <string>
#include <vector>

namespace tkacz {

class Card;

class Taxon {
public:
	Taxon& getParent();
	std::vector<Card*>& getContents();
	Taxon(std::string name);
	Taxon(std::string name, Taxon* parent, const std::initializer_list<Taxon*> children);
	virtual ~Taxon();
	const bool root = false;

protected:
	std::string name;
	Taxon &parent;
	std::vector<Taxon*> children;
	std::vector<Card*> contents;
};

} /* namespace tkacz */
