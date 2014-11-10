#pragma once

#include <memory>

#include "Command.hpp"

namespace tzcli {
	/** A MetaCommand is a very basic controller which simply invokes one of its subcommands, forwarding it all parameters but its own name. */
class MetaCommand : public Command {
public:
	MetaCommand (const char * name, const char * description, const char * longdesc=NULL, const char * lastWords=NULL, bool hidden=false);
	~MetaCommand();
	
	void addSubcommand(Command * c);
	void setBaseCommand(Command * c);
	void run(po::variables_map & args, std::vector<std::string> & others, std::string invocation) const;
	
protected:
	std::map<std::string, Command *> subcommands;
	Command * baseCommand;
};
}