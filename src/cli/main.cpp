#include <exception>
#include <iostream>

#include <boost/program_options/variables_map.hpp>
#include <boost/filesystem/path.hpp>

#include "Command.hpp"
#include "Repository.hpp"
#include "Tkacz.hpp"

using namespace tkacz;
namespace bpo = boost::program_options;
namespace bfs = boost::filesystem;

bool
    shell_mode  = false;

Tkacz::LogLevel logLevel = Tkacz::LogLevel::MESSAGE;

const void cmd_root(bpo::variables_map args) {
    std::cout << "Root executed!\n";
}

const void cmd_repo_init(bpo::variables_map args) {
    Repository::initialize(args["path"].as<bfs::path>());
}

const void cmd_shell(bpo::variables_map args) {
    shell_mode = true;
}

int main( int argc, char * argv[] ) {

    Command root {}, repo {};
    root.description = "A weird reference and knowledge management system";
    repo.description = "Repository operations ";
    root.lastWords   = "invoke with:\t-h [command [subcommand]]\tto get help on a specific command.";

    // Root level commands
    Command shell { &cmd_shell, false };
    shell.description = "Start an interactive shell";

    // Repository operations
    Command repo_init { &cmd_repo_init, false };
    repo_init.description = "Initializes a new Tkacz repository";
    repo_init.addPositionalArg("path", bpo::value<bfs::path>()->default_value("."), 1);

    repo.addSubcommand("init", &repo_init);

    root.addSubcommand("shell", &shell);
    root.addSubcommand("repo", &repo);

    try {
        root.execute(argc, argv);
    } catch (const char * e) {
        std::cout << "Fatal error: Uncaught exception.\n";
        std::cout << e  << std::endl;
    }


    if (shell_mode) {
        std::cout << "Will do shell\n";

    }
}