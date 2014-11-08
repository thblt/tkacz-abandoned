/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2014 Thibault Polge. All rights reserved.
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

#include <iostream>

#include "HandlerDispatcher.hpp"

namespace tkacz {

HandlerDispatcher::HandlerDispatcher(HandlerBase *handler) {
	forward(handler);
}

void HandlerDispatcher::forward(HandlerBase *handler) {
	stack.push( { depth, handler });
}

void HandlerDispatcher::startElement(const XMLCh* name,
		AttributeList& attributes) {
	++depth;
	stack.top().second->startElement(name, attributes);
	std::cout << *name << std::endl;;
}

void HandlerDispatcher::endElement(const XMLCh* name) {
	--depth;
	if (depth == forwardedAt) {
		stack.pop();
	}
}

void HandlerDispatcher::fatalError(const SAXParseException& exception) {
	char* message = XMLString::transcode(exception.getMessage());
	std::cout << "Fatal Error: " << message << " at line: "
			<< exception.getLineNumber() << std::endl;
	XMLString::release(&message);
	throw (exception);
}

} /* namespace */
