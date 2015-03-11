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

#include <algorithm>
#include <iostream>
#include <memory>

#include <boost/program_options.hpp>

#include "Command.hpp"

using namespace std;
namespace bpo = boost::program_options;

namespace tkacz {

Command::Command(const bool (*callback)(boost::program_options::variables_map),
                 bool metacommand)
    : callback(callback), metacommand(metacommand) {
    if (metacommand) {
        addPositionalArg("subcom", 1);
        addPositionalArg("forwardedArgs", -1);
    }
}

/**
 * @brief Adds an option to the basic group.
 */
void Command::addBasicOption(const char* name, const bpo::value_semantic* sem,
                             const char* desc) {
    addOption((int)StandardOptionGroups::Basic, name, sem, desc);
}

void Command::addBasicOption(const char* name, const char* desc) {
    addOption((int)StandardOptionGroups::Basic, name, desc);
}

void Command::addAdvancedOption(const char* name,
                                const bpo::value_semantic* sem,
                                const char* desc) {
    addOption((int)StandardOptionGroups::Advanced, name, sem, desc);
}
void Command::addAdvancedOption(const char* name, const char* desc) {
    addOption((int)StandardOptionGroups::Advanced, name, desc);
}

void Command::addHiddenOption(const char* name, const bpo::value_semantic* sem,
                              const char* desc) {
    addOption((int)StandardOptionGroups::Hidden, name, sem, desc);
}
void Command::addHiddenOption(const char* name, const char* desc) {
    addOption((int)StandardOptionGroups::Hidden, name, desc);
}

void Command::addOption(int group, const char* name,
                        const bpo::value_semantic* sem, const char* desc) {
    optionGroups[group].add_options()(name, sem, desc);
}

void Command::addOption(int group, const char* name, const char* desc) {
    optionGroups[group].add_options()(name, desc);
}

void Command::addPositionalArg(const char* name, int max, const char* desc,
                               bool createUnderlying) {
    if (max == 1)
        addPositionalArg(name, bpo::value<string>(), max, desc,
                         createUnderlying);
    else
        addPositionalArg(name, bpo::value<vector<string>>(), max, desc,
                         createUnderlying);
}

void Command::addPositionalArg(const char* name, const bpo::value_semantic* sem,
                               int max, const char* desc,
                               bool createUnderlying) {
    if (createUnderlying)
        addOption(2, name, sem, desc);
    positionalArgs.add(name, max);
}

void Command::addSubcommand(const char* name, Command* command) {
    subcommands[name] = command;
}

int Command::addOptionGroup(const char* name, bool hidden) {
    optionGroups.push_back({name});
    return optionGroups.size() - 1;
}

/**
 @brief Translates argc, argv[] to vector<string> before invoking
 execute(vector<string>, vector<string>
 */
bool Command::execute(int argc, char* argv[]) const {
    vector<string> args(argv + 1, argv + argc);
    vector<string> invoc{argv[0]};

    return execute(args, invoc);
}

bool Command::execute(char * command) const {
}

bool Command::execute(vector<string>& args, vector<string>& invocation) const {
    bpo::options_description all;
    bpo::variables_map parsed_args;
    bpo::command_line_parser parser{args};

	bool execResult = true;
		
    // FOr metacommand only
    string subcom;
    vector<string> forwardedArgs;

    for (auto od : optionGroups) {
        all.add(od);
    }

    parser.options(all).positional(positionalArgs);

    if (metacommand) {
        parser.allow_unregistered();
    }

    bpo::parsed_options parse_result = parser.run();
    bpo::store(parse_result, parsed_args);

    if (callback != nullptr) {
        if (parsed_args.count("help")) {
            printHelp(invocation);
        } else {
            execResult = callback(parsed_args);
        }
    }

    if (metacommand) {
        forwardedArgs = bpo::collect_unrecognized(parse_result.options,
                                                  bpo::include_positional);
        if (parsed_args.count("subcom")) {
            subcom = parsed_args["subcom"].as<string>();

            // Remove subcom name from args to forward.
            forwardedArgs.erase(
                find(forwardedArgs.begin(), forwardedArgs.end(), subcom));
            // Append to invocation
            invocation.push_back(subcom);
        } else {
            if (!execResult) { printHelp(invocation); }
            return execResult;
        }
    }

    if (metacommand) {
        std::map<string, Command*>::const_iterator subcommand =
            subcommands.find(subcom);

        if (subcommand == subcommands.end()) {
            printHelp(invocation, "Subcommand doesn't exist");
            return false;
        } else {
            subcommand->second->execute(forwardedArgs, invocation);
        }
    }

    return true;
}

void Command::printHelp(vector<string> invocation, string errorMsg) const {
    bool onError = !errorMsg.empty();

    if (onError) {
        cout << "ERROR: " << errorMsg << endl << endl;
    } // else {
    cout << (name.empty() ? invocationString(invocation) : name) << " — "
         << description << "." << endl;

    if (!longDesc.empty())
        cout << longDesc << endl << endl;
    //}

    if (metacommand) {
        cout << "\nSubcommands:\n";
        for (auto command : subcommands) {
            cout << "  " << command.first << "\t\t" << command.second->description
                 << endl;
        }
    }

    for (uint i = 0; i < optionGroups.size(); i++) {
        if (hiddenOptionGroups.find(i) == hiddenOptionGroups.end() and
            optionGroups[i].options().size())
            cout << "\n" << optionGroups[i] << "\n";
    }

    if (!onError and !lastWords.empty())
        cout << lastWords << endl << endl;
}

string Command::invocationString(vector<string>& invocation, string prefix,
                                 string suffix) const {
    string out;
    bool first = true;
    for (auto i : invocation) {
        if (first)
            first = false;
        else
            out += " ";
        out += i;
    }
    if (out.empty())
        return (out);
    return (prefix + out + suffix);
}
}
