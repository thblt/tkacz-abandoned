/*                                                                 [licblock]
 * This file is part of Tkacz.
 * Copyright (c) 2012-2014 Thibault Polge. All rights reserved.
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

using namespace tkacz;
namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

#include <memory>
#include <boost/shared_ptr.hpp>
#include <boost/make_shared.hpp>
#include <boost/python.hpp>
using namespace boost::python;
namespace bp = boost::python;

bool shell_mode = false;

Tkacz::LogLevel logLevel = Tkacz::LogLevel::INFO;

const void cmd_root(bpo::variables_map args) {
  std::cout << "Root executed!\n";
}

const void cmd_repo_init(bpo::variables_map args) {
  Repository::initialize(args["path"].as<bfs::path>());
}

const void cmd_shell(bpo::variables_map args) { shell_mode = true; }

int main(int argc, char *argv[]) {

  Command root{};
  int globalOption = root.addOptionGroup("Global options");
  root.name = "Tkacz";
  root.description = "A weird reference and knowledge management system";
  root.lastWords = "invoke with:\t-h [command [subcommand]]\tto get help on a "
                   "specific command.";

  root.addOption(globalOption, "verbose,v",
                 "Throw lots and lots of garbage on stdout");
  root.addOption(globalOption, "quiet", "Completely disable output");
  root.addOption(globalOption, "no-interaction",
                 "No interaction (script) mode");

  // Root level commands
  Command shell{&cmd_shell, false};
  shell.description = "Start an interactive shell";

  // Repository operations
  Command repo_init{&cmd_repo_init, false};
  repo_init.description = "Initializes a new Tkacz repository";
  repo_init.addPositionalArg("path",
                             bpo::value<bfs::path>()->default_value("."), 1);

  root.addSubcommand("init", &repo_init);

  root.addSubcommand("shell", &shell);
  root.addSubcommand("init", &repo_init);

  try {
    root.execute(argc, argv);
  } catch (Exception &e) {
    std::cout << "Fatal error (uncaught exception): ";
    std::cout << e.what() << std::endl;
  }

  if (shell_mode) {
    std::cout << "Will do shell\n";
  }
}