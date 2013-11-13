#pragma once

#include <string>

namespace tkacz {

class Node;

/**
 * @brief A Schema is a constraint for a Node.
 *
 * Schema itself is a purely virtual class. There is a one-to-one relationship between
 * the Template class hierarchy and the Node hierarchy, ie, every ValueNode uses a
 * ValueSchema object, every EntityNode uses an EntityTemplate, and so on.
 *
 * @ingroup schemas
 */
class Schema {
public:
	const std::string name;

	/** @brief Builds a new Node with this Schema **/
	template<typename args> Node make(args...);

	Schema(std::string name) : name(name) {};
	virtual ~Schema();
};

}
