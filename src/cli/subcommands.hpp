#pragma once

#include <string>

namespace tzcli {

	// int cmd_init(std::vector<std::string> args);
	int cmd_init(std::vector<std::string> args);
	
	int cmd_card_new(std::vector<std::string> args);
	int cmd_card_rm(std::vector<std::string> args);
	int cmd_card_edit(std::vector<std::string> args);
	int cmd_card_view(std::vector<std::string> args);

}