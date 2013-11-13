#pragma once 

#include "Store.hpp"

namespace tkacz {

class MongoDbStore: Store {
public:
	MongoDbStore();
	virtual ~MongoDbStore();
};

}
