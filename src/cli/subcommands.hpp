#pragma once

#include <string>

#include "Command.hpp"

namespace tzcli {

class CmdInit : public Command {
public:
	CmdInit();
	void run(po::variables_map & args, std::vector<std::string> & others, std::vector<const char *> & invocation) const;
};
}