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
