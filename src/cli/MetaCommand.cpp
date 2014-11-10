#include <iostream>

#include "MetaCommand.hpp"
#include "Tkacz.hpp"

namespace tzcli {
MetaCommand::MetaCommand () {
	addPositionalArg("catchall", -1);
	initialize();
}

MetaCommand::~MetaCommand() {
	// @TODO delete all pointers in this->subcommands. 
}

void MetaCommand::addSubcommand(const char * name, Command * c) {
	subcommands[name] = c;
}

void MetaCommand::run(po::variables_map & args, std::vector<std::string> & others, std::vector<const char *> & invocation) const {
	
	Command * subcom = NULL;
	const char * subcom_name;
		
	if (others.size() > 0) {
	subcom_name = others[0].c_str();
	if (subcommands.find(subcom_name) != subcommands.end()) 
		subcom = subcommands.at(subcom_name); }
	
//		tkacz::debug_msg() << "Subcommand in " << name << " called " <<  subcom_name << std::endl;
	
	if (subcom!=NULL)
		if (args.count("help")) {
			subcom->printHelp(false, invocation);  // @FIXME This won't work with nested MetaCommands
			return;
		} else {
			subcom->execute( others, invocation );
		}
	else {
		if (!strlen(subcom_name)) {
			tkacz::warn() << invocationString(invocation) << "Unknown command: " << subcom_name << "\n";
		}
		printHelp(!strlen(subcom_name), invocation);
	}
}

}
