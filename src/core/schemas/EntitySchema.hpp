#pragma once

#include <map>
#include <string>

#include "Schema.hpp"

namespace tkacz {

class Node;

class EntitySchema: public Schema {
public:
	EntitySchema(std::string name);
	~EntitySchema();

	bool insertAttribute(std::string name, Node &value);
	bool removeAttribute(std::string name, Node &value);
	bool updateAttribute(std::string name, Node &value);
	bool move(std::string name, Node &value);
	bool remove(std::string name, Node &value);

protected:
	std::map<std::string, Schema*> tplData;
};

} /* namespace tkacz */
