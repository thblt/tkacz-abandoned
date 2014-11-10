#include <boost/program_options.hpp>

#include "Command.hpp"
#include "Tkacz.hpp"

namespace tzcli {

	Command::Command (const char * name, const char * description, const char * longdesc, const char * lastWords, bool hidden, bool allowUnregistered, bool autoHelp) :
		name(name),
		description(description),
		longDesc(longdesc),
		lastWords(lastWords),
		hidden(hidden),
		allowUnregistered(allowUnregistered),
		autoHelp(autoHelp)
	{}
		
	void Command::addBasicOption(const char * name, const po::value_semantic * sem, const char * desc) {
		addOption(0, name, sem, desc);
	}
	void Command::addBasicOption(const char * name, const char * desc) {
		addOption(0, name, desc);
	}

	void Command::addAdvancedOption(const char * name, const po::value_semantic * sem, const char * desc) {
		addOption(1, name, sem, desc);
	}
	void Command::addAdvancedOption(const char * name, const char * desc) {
		addOption(1, name, desc);
	}

	void Command::addHiddenOption(const char * name, const po::value_semantic * sem, const char * desc) {
		addOption(3, name, sem, desc);
	}
	void Command::addHiddenOption(const char * name, const char * desc) {
		addOption(3, name, desc);
	}
	
	void Command::addOption(int group, const char * name, const po::value_semantic * sem, const char * desc) {
		optionGroups[group].add_options()(name, sem, desc);
	}
	void Command::addOption(int group, const char * name, const char * desc) {
		optionGroups[group].add_options()(name, desc);
	}
	
	void Command::addPositionalArg(const char * name, int max, bool createUnderlying) {
		if (max == 1) 
			addPositionalArg(name, po::value<std::string>(), max, createUnderlying);
		else 
			addPositionalArg(name, po::value<std::vector<std::string>>(), max, createUnderlying);
	}
			
	void Command::addPositionalArg(const char * name, const po::value_semantic * sem, int max, bool createUnderlying) {
		if (createUnderlying) 
			addOption(2, name, sem, "");
		positionalArgs.add(name, max);
	}
	
	bool Command::execute(int argc, char * argv [], std::string invocationPrefix) const {
		return execute(std::vector<std::string> (argv, argv + argc), invocationPrefix);
	}
	
	bool Command::execute(std::vector<std::string> args, std::string invocationPrefix) const {
		
		po::options_description 	all;
		po::variables_map 			parsed_args;
		std::vector<std::string> 	unrecognized;
		
		invocationPrefix += args.at(0) + " ";
		
		args.erase(args.begin());
	
		for (auto od : optionGroups) {
			all.add(od);
			}
			
		try {
			po::command_line_parser parser { args };
			parser.options(all).
				positional(positionalArgs);
			
			if (allowUnregistered)
				parser.allow_unregistered();
			
			po::parsed_options parse_result = parser.run();
			
			po::store(parse_result, parsed_args);
			unrecognized = po::collect_unrecognized(parse_result.options, po::include_positional);
		
		} catch (std::exception &e) {
			tkacz::warn() << invocationPrefix << "error: " << e.what() << std::endl;
			return false;
		}

		// ------------

		// tkacz::debug_msg("---\nParsed arguments\n");
		// for (auto a : parsed_args)
		// 		tkacz::debug_msg() << "\t" << a.first << " = " << a.second.as<std::string>() << std::endl;
		// //                                                               ^ will crash on vector<something>            
		//
		// tkacz::debug_msg("\nUnrecognized args\n");
		// for (auto a : unrecognized)
		// 	tkacz::debug_msg() << "\t" << a << std::endl;
		// tkacz::debug_msg("---\n");
		// ------------

		if (autoHelp and parsed_args.count("help")){
			printHelp(false, invocationPrefix);
			return true;
		}
		run(parsed_args, unrecognized, invocationPrefix);
		return true;
	}
		
  	void Command::initialize() {
		// tkacz::debug_msg() << "initialize() " << name << std::endl;

		addBasicOption("help,h", "Display this help.");
		
		addHiddenOption("__invocation-prefix", po::value<std::string>(), "Base call used for subcommand invocation");	
		addHiddenOption("__invocation-ignored-args", po::value<int>(),  "Number of args to ignore at beginning of argv");
	}
	
	void Command::printHelp(bool onError, std::string invocationPrefix) const {
		if (!onError) {
			tkacz::say() << invocationPrefix << "— " << description << "." << std::endl << std::endl;			
		
		 if (longDesc != NULL)
			 tkacz::say() << longDesc << std::endl << std::endl;
		 }
		 		 
		 for (int i = 0; i < optionGroups.size(); i++) {
			 if (hiddenOptionGroups.find(i) == hiddenOptionGroups.end() and optionGroups[i].options().size())
				 tkacz::say() << optionGroups[i] << std::endl;
		 }
		 
		 if (!onError and lastWords != NULL) 
			 tkacz::say() << lastWords << std::endl << std::endl;
		 
		
		
	}
}