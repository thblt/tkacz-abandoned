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
