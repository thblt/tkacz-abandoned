#pragma once

#include <string>

namespace tkacz {

/**
 * A Primitive holds a simple value, such as an integer, a string or a float.
 */
template <typename T>
class TZPrimitive {
public:
	virtual T& getValue();

protected:
	T value;

	TZPrimitive();
	virtual ~TZPrimitive();
};

class TZString: public TZPrimitive<std::string> {};
class TZInteger : public TZPrimitive<long long int> {};
class TZFloat: public TZPrimitive<long double> {};
}
