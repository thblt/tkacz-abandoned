/*
 * RootNode.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: thblt
 */

#include <cassert>

#include "RootNode.hpp"
#include "EntitySchema.hpp"

namespace tkacz {

RootNode::RootNode(EntitySchema &schema) : EntityNode(nullptr) {
	assert(schema.isRootSchema());
}

RootNode::~RootNode() {
	// TODO Auto-generated destructor stub
}

}
