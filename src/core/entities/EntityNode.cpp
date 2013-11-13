/*
 * TZEntity.cpp
 *
 *  Created on: 7 nov. 2013
 *      Author: thblt
 */

#include <iostream>

#include "Node.hpp"
#include "EntityNode.hpp"
#include "EntitySchema.hpp"

namespace tkacz {

EntityNode::EntityNode(EntityNode &parent, EntitySchema &schema) : parent(parent), schema(schema) {
	// TODO Auto-generated constructor stub
}

EntityNode::~EntityNode() {
}

}
