#include <iostream>

#include <boost/filesystem.hpp>
#include <git2/repository.h>

#include "Repository.hpp"

namespace bfs = boost::filesystem;

namespace tkacz {

    Repository::Repository(const bfs::path & path) {

    }

    Repository Repository::initialize (const bfs::path & path, bool force) {

        if (!bfs::exists(path))
            throw "Root path doesn't exist";

        if (!bfs::is_directory(path)) {
            throw "Root path isn't a directory";
        }

        if (!bfs::is_empty(path)) {
            throw "Root path isn't empty";
        }

        std::cout << bfs::status(path).permissions();
        
        return { path };
        
    }
    
}
