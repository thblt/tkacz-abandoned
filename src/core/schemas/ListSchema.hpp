#pragma once 

namespace tkacz {

class Schema;

class ListSchema {
public:
	ListSchema(Schema &schema, int min=1, int max=0);
	virtual ~ListSchema();

protected:
	Schema &schema;
	long int min, max;
};

} /* namespace tkacz */
