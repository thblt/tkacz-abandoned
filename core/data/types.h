#pragma once

namespace tkacz {

class Type {
public:
	Type();
	virtual ~Type();
};

class Card : public Type {};

};
