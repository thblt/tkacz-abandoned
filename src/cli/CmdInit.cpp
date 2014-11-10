#include <boost/program_options.hpp>
#include <boost/filesystem.hpp>

#include "Command.hpp"
#include "subcommands.hpp"
#include "Tkacz.hpp"
#include "Repository.hpp"

using namespace boost::filesystem;
using namespace boost::program_options;
using namespace std;
using namespace tkacz;

namespace tzcli {

	void CmdInit::run(po::variables_map & args, std::vector<std::string> & others, std::string invocation) const {
		tkacz::say("Initialize repository in:" ) << args["path"].as<path>() << endl;
	}
	
	CmdInit::CmdInit() : Command("init", "Initializes a new, empty Tkacz repository") {
		addBasicOption("mkdir,m",         "Create base directory if needed");
		addBasicOption("mkinterm,i",      "Create full path to repository");
		
		addPositionalArg("path", po::value<bfs::path>()->default_value("."), 1, "Where to create this repository");
		
		initialize();
	}
}