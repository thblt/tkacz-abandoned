#pragma once

#include <memory>

#include "Command.hpp"

namespace tzcli {
	/** A MetaCommand is a very basic controller which simply invokes one of its subcommands, forwarding it all parameters but its own name. */
class MetaCommand : public Command {
public:
	MetaCommand ();
	~MetaCommand();
	
	void addSubcommand(const char * name, Command * c);
	void setBaseCommand(Command * c);
	void run(po::variables_map & args, std::vector<std::string> & others, std::vector<const char *> & invocation) const;
	
protected:
	std::map<std::string, Command *> subcommands;
	Command * baseCommand;
};
}