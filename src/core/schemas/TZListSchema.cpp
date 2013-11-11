/*
 * TZListSchema.cpp
 *
 *  Created on: 10 nov. 2013
 *      Author: thblt
 */

#include "TZListSchema.h"
#include "TZSchema.h"

namespace tkacz {

ListSchema::ListSchema(Schema &schema, int min, int max) :
		schema(schema), min(min), max(max) {
	// TODO Auto-generated constructor stub

}

ListSchema::~ListSchema() {
	// TODO Auto-generated destructor stub
}

} /* namespace tkacz */
