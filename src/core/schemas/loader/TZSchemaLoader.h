#pragma once 

#include <string>
#include <vector>

namespace tkacz {

class Entity;

class SchemaLoader {
public:
	SchemaLoader();
	virtual ~SchemaLoader();

	std::vector<Entity> operator()();

protected:
	std::string path;
};

}
