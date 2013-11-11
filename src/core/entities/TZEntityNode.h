/*
 * TZEntity.h
 *
 *  Created on: 7 nov. 2013
 *      Author: thblt
 */

#pragma once

#include <string>
#include <map>
#include <vector>

#include "TZNode.h"

namespace tkacz {

class Card;
class EntitySchema;
class Schema;

/**
 * @brief
 * @ingroup data
 */
class EntityNode : public Node {
public:
	EntityNode(EntityNode &parent, EntitySchema &schema);
	virtual ~EntityNode();

	void set(std::string name, Node &value);
	void operator[](std::string name);

protected:
	EntityNode &parent;
	EntitySchema &schema;
	std::map <std::string, Node> attributes;
	std::vector<std::string> disabledAttributes;
};
}
