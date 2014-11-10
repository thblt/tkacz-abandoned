// #include <iostream>
// #include <string>
// #include <vector>
//
// #include <boost/filesystem.hpp>
//
// #include <Repository.hpp>
//
// #include <boost/program_options.hpp>
//
// #include "Command.hpp"
// #include "subcommands.hpp"
// #include "Tkacz.hpp"
//
// namespace po = boost::program_options;
//
// namespace bfs = boost::filesystem;
//
// namespace tzcli {
//
// 	void cmd_init(std::vector<std::string> args) {
// 		po::options_description options = get_default_options_description(),
// 			advanced("Advanced options"),
// 			hidden,
// 			all;
// 		po::positional_options_description positional;
// 		options.add_options()
// 			("mkdir,M",         "Create base directory if needed")
// 			("mkinterm,I",      "Create full path to repository");
// 		advanced.add_options()
// 			("no-bundle",       "Do not set bundle flag on MacOS X");
//
// 		hidden.add_options()
// 	    	("path",            po::value<bfs::path>()->default_value("."), "Where to create the repository");
// 		positional.add
// 			("path", 1);
//
// 		all.add(options).add(advanced).add(hidden);
//
// 		po::variables_map settings;
//
// 		po::store(po::command_line_parser(args).
// 		options(all).
// 		positional(positional).
// 		run(), settings);
//
// 		std::cout << options << advanced;
// 	}
// }