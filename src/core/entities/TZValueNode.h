#pragma once

#include <vector>

#include "TZNode.h"

namespace tkacz {

template<typename T> class ValueNode: public tkacz::Node {
public:
	ValueNode();
	virtual ~ValueNode();

	T& operator[](int &i) {
		return &this->data[i];
	}

protected:
	T data;
};

}
