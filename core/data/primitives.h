#pragma once

namespace tkacz {

template <typename T>
class Primitive {
public:
	virtual void operator=(std::string input) = 0;
	virtual void operator=(T input) = 0;

protected:
	T value;

//	virtual Primitive();
//	virtual ~Primitive();
};

class TZPInteger : public Primitive<int> {

};


}
