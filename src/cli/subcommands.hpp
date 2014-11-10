#pragma once

#include <string>

#include "Command.hpp"

namespace tzcli {

class CmdInit : public Command {
public:
	CmdInit();
	~CmdInit() {
		tkacz::debug_msg() << "~CmdInit(): " << name << std::endl;
	}
	
	void run(po::variables_map & args, std::vector<std::string> & others, std::string invocation) const;
};
}