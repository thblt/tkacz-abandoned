/*
 * TZEntity.h
 *
 *  Created on: 7 nov. 2013
 *      Author: thblt
 */

#pragma once

#include <string>
#include <map>

#include "TZObject.h"
#include "TZCard.h"
#include "TZEntityTemplate.h"

namespace tkacz {

/**
 * @brief
 * @ingroup data
 */
class Entity : public Object {
public:
	Entity(EntityTemplate &tpl);
	virtual ~Entity();
//
//	Entity & operator[](std::string attr) {
//		return this;
//	};

protected:
	std::map<std::string, Entity> dEntities;
	std::map<std::string, long int> dIntegers;
	std::map<std::string, long float> dFloats;
	std::map<std::string, Card*> dRelationships;
	const Template &tpl;
};

}
