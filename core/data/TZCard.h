#pragma once

#include "TZEntity.h"
#include "TZTemplate.h"

namespace tkacz {

/**
 * @brief A Tkacz “card”.
 * @ingroup data
 */
class Card: public Entity {
public:
	/**
	 * @brief Creates a new card of Type t
	 * @param t
	 */
	Card(EntityTemplate &t);
	virtual ~Card();
};

} /* namespace tkacz */
