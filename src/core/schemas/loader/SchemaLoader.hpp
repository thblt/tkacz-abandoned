#pragma once 

#include <string>

#include <expat.h>

namespace tkacz {

class SchemaLoader {
public:
	/** @brief Loads a schema.
	 *
	 * WARNING This class is pure static.
	 *
	 * @param xmlFile The root file to parse. Use Xincludes to add extra files.
	 */
	static void load(std::string xmlFile);

	static void startElement(void *data, const char *element, const char **attribute);
	static void endElement(void *data, const char *el);

protected:
	std::string xmlFile;

private:
	SchemaLoader();
};

} /* namespace tkacz */
