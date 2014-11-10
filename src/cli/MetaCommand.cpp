#include <iostream>

#include "MetaCommand.hpp"
#include "Tkacz.hpp"

namespace tzcli {
MetaCommand::MetaCommand (const char * name, const char * description, const char * longdesc, const char * lastWords, bool hidden) : Command( name, description, longdesc, lastWords, hidden, true, false) {
	addPositionalArg("catchall", -1);
	
	initialize();
}

MetaCommand::~MetaCommand() {
	// @TODO delete all pointers in this->subcommands. 
}

void MetaCommand::addSubcommand(Command * c) {
	subcommands[c->name] = c;
}

void MetaCommand::run(po::variables_map & args, std::vector<std::string> & others, std::string invocation) const {
	
	Command * subcom = NULL;
	std::string subcom_name;
		
	if (others.size() > 0) {
	subcom_name = others.at(0);
	if (subcommands.find(subcom_name) != subcommands.end()) 
		subcom = subcommands.at(subcom_name); }
	
//		tkacz::debug_msg() << "Subcommand in " << name << " called " <<  subcom_name << std::endl;
	
	if (subcom!=NULL)
		if (args.count("help")) {
			subcom->printHelp(false, invocation+" "+subcom_name);  // @FIXME This won't work with nested MetaCommands
			return;
		} else {
			subcom->execute( others, invocation );
		}
	else {
		if (!subcom_name.empty()) {
			tkacz::warn() << invocation << "Unknown command: " << subcom_name << "\n";
		}
		printHelp(!subcom_name.empty());
	}
}

}
