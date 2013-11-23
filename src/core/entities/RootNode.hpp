#pragma once 

#include "EntityNode.hpp"

namespace tkacz {

class EntitySchema;

class RootNode: public tkacz::EntityNode {
public:
	RootNode(EntitySchema &schema);
	virtual ~RootNode();
};

} /* namespace tkacz */
