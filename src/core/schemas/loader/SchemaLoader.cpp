/*
 * SchemaLoader.cpp
 *
 *  Created on: 21 nov. 2013
 *      Author: thblt
 */

#include <expat.h>

#include "SchemaLoader.hpp"

namespace tkacz {

void SchemaLoader::load(std::string xmlFile) {
	XML_Parser parser = XML_ParserCreate("UTF-8");
	XML_SetElementHandler(parser, startElement, endElement);

//	XML_SetElementHandler(parser,
//			[this](void *data, const char *element, const char **attribute) {
//				this->startElement(data, element, attribute);
//			}, [this](void *data, const char *element) {
//				this->endElement(data, element);
//			});
}

} /* namespace tkacz */
