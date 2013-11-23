#pragma once 

#include <stack>
#include <utility>

#include <xercesc/sax/HandlerBase.hpp>

XERCES_CPP_NAMESPACE_USE;

namespace tkacz {

class HandlerDispatcher: public HandlerBase {
public:
	HandlerDispatcher(HandlerBase *handler);

	void startElement(const XMLCh* name, AttributeList& attributes);
	void endElement(const XMLCh* name);
	void fatalError(const SAXParseException& exception);

	void forward(HandlerBase *handler);

protected:
	std::stack<std::pair<int, HandlerBase*>> stack;
	HandlerBase* forwardTo;
	int forwardedAt, depth = 0;
};

}
