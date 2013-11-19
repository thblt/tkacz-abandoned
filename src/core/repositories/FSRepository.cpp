/*
 * TZFilesystemRepository.cpp
 *
 *  Created on: 12 nov. 2013
 *      Author: thblt
 */

#include <iostream>

#include <boost/filesystem.hpp>

#include "FSRepository.hpp"

namespace bfs = boost::filesystem;

namespace tkacz {

const bfs::path FSRepository::dataPath = ".tkacz",
FSRepository::manifestFile = "manifest";

FSRepository::FSRepository(const std::string & path)
		throw (NotARepositoryException, MalformedRepositoryException,
		FileNotFoundException) {

	std::cout << "Creating FSRepository from " << path << std::endl;

	if (!bfs::exists(path))
		throw FileNotFoundException();

	if (bfs::is_regular_file(path)) {
		isZipBundle = true;
	} else if (bfs::is_directory(path)) {
		isZipBundle = false;
	} else {
		throw NotARepositoryException();
	}

}

FSRepository::~FSRepository() {
}

}
