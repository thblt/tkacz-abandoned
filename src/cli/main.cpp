#include <iostream>
#include <memory>

// #include <boost/program_options.hpp>

#include "tzbuild.h"
#include "subcommands.hpp"
#include "MetaCommand.hpp"
#include "Tkacz.hpp"

namespace po = boost::program_options;
using namespace std;
using namespace tzcli;

tkacz::LogLevel loglevel = tkacz::LogLevel::MESSAGE;
bool quiet = false,
shell = false;

int main(int argc, char* argv[]) {

	po::variables_map args; std::vector<std::string> others;// DEBUG, remove

	MetaCommand root;

	root.description = "A weird reference and knowledge management system";

	root.addSubcommand("init", new CmdInit());

	std::vector<const char *> invocationStack { argv[0] };

	root.execute(argc, argv, invocationStack);
	
	return 0;
//
// 	map<string, int(*)(std::vector<string>)> routes {
// 		{ "init",              &cmd_init },
// 		{ "new",               &cmd_init }
// 	};
//
// 	 po::options_description root_options_desc("Global parameters");
// 	 root_options_desc.add_options()
// 		 ("verbose,v",       "Throws lots of garbage on stdout")
// 		 ("quiet",           "Do not print anything on stdout/stderr (equivalent to -v 0)")
// 		 ("version,V",       "Print version number and exit")
// 	     ("help,h",          "Show help");
//
// 	po::variables_map root_options;
//
// 	po::parsed_options parsed = po::command_line_parser(argc, argv).
// 		options(root_options_desc).
// 		allow_unregistered().
// 		run();
//
// 	po::store(parsed, root_options);
//
// 	if (root_options.count("version")) {
// 		cout << "Tkacz " << TZ_VERSION_STRING << endl;
// 		exit(0);
// 	}
//
// 	if (root_options.count("verbose"))
// 		loglevel = tkacz::LogLevel::_ALL;
//
// 	if (root_options.count("quiet"))
// 		loglevel = tkacz::LogLevel::_NONE;
//
// 	std::vector<std::string> subcommand_options = po::collect_unrecognized(parsed.options, po::include_positional);
//
// 	string subcom;
// 	if (subcommand_options.size()>0) {
// 		subcom = subcommand_options[0];
// 		}
//
// 	if (subcom.empty()) {
// 		print_help();
// 		exit(-1);
// 	}
//
// 	if (routes.find(subcom) != routes.end()) {
// 		subcommand_options.erase(subcommand_options.begin());
// 		routes.at(subcom)(subcommand_options);
// 	} else {
// 		tkacz::fatal() << "Not a valid command or parameter: " << subcom << endl;
// 		print_help();
// 	}
//
// 	exit(0);
}