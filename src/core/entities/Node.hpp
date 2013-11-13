/*
 * TZObject.h
 *
 *  Created on: 7 nov. 2013
 *      Author: thblt
 */

#pragma once

#include <map>

namespace tkacz {

class EntityNode;

class Node {

public:
	friend class Schema;

	Node();
	virtual ~Node();

	/**
	 * Returns this Node's path from root Entity.
	 **/
	std::string path();

	/**
	 * @brief Returns the number of elements in this node. If this node has children, it returns the number of children,
	 * else the number of values of the same type.
	 * @return A positive or null integer.
	 */
	int len();

	Node &getParent();

	Node &move(EntityNode &parent);

protected:
};

}
