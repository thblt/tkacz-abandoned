/*                                                                 [licblock]
 * This file is part of Tkacz. 
 * Copyright (c) 2012-2015 Thibault Polge. All rights reserved.
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 * 
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *                                                                [/licblock] */

#include <exception>
#include <iostream>

#include <boost/program_options/variables_map.hpp>
#include <boost/filesystem/path.hpp>

#include "Command.hpp"
#include "Exception.hpp"
#include "Repository.hpp"
#include "Tkacz.hpp"
#include "Version.hpp"
#include "tzbuild.h"

using namespace tkacz;
namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

const Version cliVersion {
	TZ_VERSION_MAJOR,
    TZ_VERSION_MINOR,
	TZ_VERSION_PATCH,
	Version::Maturity::TZ_VERSION_MATURITY,
	TZ_VERSION_PREVERSION,
	TZ_VERSION_NAME };

bool shell_mode = false;

Tkacz::LogLevel logLevel = Tkacz::LogLevel::INFO;

const bool cmd_root(bpo::variables_map args) {
	if (args.count("version")) {
		std::cout << TZ_APP_NAME << " " << Tkacz::version << " (CLI " << cliVersion << ")." << endl;
		return true;
	}
	
	return false;
}

const bool cmd_repo_init(bpo::variables_map args) {
    Repository::initialize(args["path"].as<bfs::path>());
	return false;
}

const bool cmd_shell(bpo::variables_map args) { 
	shell_mode = true; 
	return true; 
}

int main(int argc, char* argv[]) {

    Command root{ &cmd_root, true };
    int globalOption = root.addOptionGroup("Global options");
    root.name = "Tkacz";
    root.description = "A weird reference and knowledge management system";
    root.lastWords =
        "invoke with:\n\t-h [command [subcommand]]\nto get help on a "
        "specific command.";

    root.addOption(globalOption, "verbose,v",
                   "Throw lots and lots of garbage on stdout");
    root.addOption(globalOption, "quiet", "Completely disable output");
    root.addOption(globalOption, "no-interaction",
                   "No interaction (script) mode");
    root.addOption(globalOption, "version",
                   "Print version number and exit");
	root.addOption(globalOption, "help,h", "Display this help");


    // Root level commands
    Command shell{&cmd_shell, false};
    shell.description = "Start an interactive shell";

    // Repository operations
    Command repo_init{&cmd_repo_init, false};
    repo_init.description = "Initialize a new Tkacz repository";
    repo_init.addPositionalArg("path",
                               bpo::value<bfs::path>()->default_value("."), 1);

    root.addSubcommand("init", &repo_init);

    root.addSubcommand("shell", &shell);
    root.addSubcommand("init", &repo_init);

	Tkacz::init();

    try {
        root.execute(argc, argv);
    } catch (Exception& e) {
        std::cout << "Fatal error (uncaught exception): ";
        std::cout << e.what << std::endl;
    }

    if (shell_mode) {
		char command[65536];
		while(true) {
			cout << ">> ";
			cin.getline(command, 65536);
			cout << "Shell not implemented." << endl;
		}
    }
}