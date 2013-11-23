/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2013 Thibault Polge. All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                [/licblock] */

#pragma once 

#include "Exception.hpp"

namespace tkacz {

class Card;
class EntityTemplate;

/**
 * @brief This exception is thrown whenever a children class of Repository was
 * asked to open a repository and got something that either doesn't look like
 * a Tkacz repository or seemed damaged.
 *
 * This exception may be subclassed if different types of problems should be reported.
 * @ingroup repositories
 * @ingroup exceptions
 */
class MalformedRepositoryException: public Exception {
};

/**
 * @brief This exception is thrown whenever a children class of Repository was
 * asked to open something that definitely doesn't look like a Tkacz repository.
 * This exception should be preferred over MalformedRepositoryException when there
 * doesn't seem to be any way to get any data from the given location.
 *
 * This exception may be subclassed if different types of problems should be reported.
 * @ingroup repositories
 * @ingroup exceptions
 */
class NotARepositoryException: public Exception  {
};

/**
 * @brief A base interface for Tkacz repositories.
 * @ingroup repositories
 */
class Repository {
};
}
