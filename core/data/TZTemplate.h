#pragma once

namespace tkacz {

/**
 * @brief A Template is a constraint for an \ref Object.
 *
 * Template itself is a purely virtual class. There is a one-to-one relationship between
 * the Template class hierarchy and the Object hierarchy, ie, every Primitive uses a
 * PrimitiveTemplate object and every Entity and Card uses an EntityTemplate.
 *
 * @ingroup data
 */
class Template {
public:
	virtual bool isEntity() = 0;
	virtual bool isPrimitive() = 0;
	virtual bool isCard() = 0;
	Template();
	virtual ~Template();
};

}
