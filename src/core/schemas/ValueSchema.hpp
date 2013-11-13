#pragma once 

#include "Schema.hpp"

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
