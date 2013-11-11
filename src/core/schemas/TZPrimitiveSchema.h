#pragma once

#include <string>

#include "TZSchema.h"

namespace tkacz {

/**
 * A Primitive holds a simple value, such as an integer, a string or a float.
 */
template<typename T>
class PrimitiveTemplate: public Schema {
public:
	virtual T& getValue();

protected:
	T value;

	PrimitiveTemplate();
	virtual ~PrimitiveTemplate();
};

}
