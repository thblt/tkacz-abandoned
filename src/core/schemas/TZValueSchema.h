#pragma once 

#include "TZSchema.h"

namespace tkacz {

/*
 *
 */
template <typename T> class ValueSchema: public Schema {
public:
	ValueSchema();
	virtual ~ValueSchema();
};
}
