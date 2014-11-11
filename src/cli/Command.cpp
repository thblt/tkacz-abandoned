#include <memory>

#include <boost/program_options.hpp>

#include "Command.hpp"
#include "Tkacz.hpp"

namespace tzcli {

void Command::addBasicOption(const char * name, const po::value_semantic * sem,
		const char * desc) {
	addOption(0, name, sem, desc);
}
void Command::addBasicOption(const char * name, const char * desc) {
	addOption(0, name, desc);
}

void Command::addAdvancedOption(const char * name,
		const po::value_semantic * sem, const char * desc) {
	addOption(1, name, sem, desc);
}
void Command::addAdvancedOption(const char * name, const char * desc) {
	addOption(1, name, desc);
}

void Command::addHiddenOption(const char * name, const po::value_semantic * sem,
		const char * desc) {
	addOption(3, name, sem, desc);
}
void Command::addHiddenOption(const char * name, const char * desc) {
	addOption(3, name, desc);
}

void Command::addOption(int group, const char * name,
		const po::value_semantic * sem, const char * desc) {
	optionGroups[group].add_options()(name, sem, desc);
}
void Command::addOption(int group, const char * name, const char * desc) {
	optionGroups[group].add_options()(name, desc);
}

void Command::addPositionalArg(const char * name, int max,
		bool createUnderlying) {
	if (max == 1)
		addPositionalArg(name, po::value<std::string>(), max, createUnderlying);
	else
		addPositionalArg(name, po::value<std::vector<std::string>>(), max,
				createUnderlying);
}

void Command::addPositionalArg(const char * name,
		const po::value_semantic * sem, int max, bool createUnderlying) {
	if (createUnderlying)
		addOption(2, name, sem, "");
	positionalArgs.add(name, max);
}

bool Command::execute(int argc, char * argv[],
		std::vector<const char *> & invocation) const {
	return execute(std::vector<std::string>(argv, argv + argc), invocation);
}

bool Command::execute(std::vector<std::string> args,
		std::vector<const char *> & invocation) const {

	po::options_description all;
	po::variables_map parsed_args;
	std::vector<std::string> unrecognized;

	if (args.size() == 0) {
		tkacz::severe("Anomalous state: args vector has null size.");
	}

	char * cmdname;
	strcpy(cmdname, args.at(0).c_str());
	invocation.push_back(cmdname);
	args.erase(args.begin());

	for (auto od : optionGroups) {
		all.add(od);
	}

	try {
		po::command_line_parser parser { args };
		parser.options(all).positional(positionalArgs);

		if (allowUnregistered)
			parser.allow_unregistered();

		po::parsed_options parse_result = parser.run();

		po::store(parse_result, parsed_args);
		unrecognized = po::collect_unrecognized(parse_result.options,
				po::include_positional);

	} catch (std::exception &e) {
		tkacz::warn() << invocationString(invocation) << "error: " << e.what()
				<< std::endl;
		return false;
	}

	if (autoHelp and parsed_args.count("help")) {
		printHelp(false, invocation);
		return (true);
	}
	run(parsed_args, unrecognized, invocation);
	return (true);
}

void Command::initialize() {
	if (autoHelp)
		addBasicOption("help,h", "Display this help.");

	addHiddenOption("__invocation-prefix", po::value<std::string>(),
			"Base call used for subcommand invocation");
	addHiddenOption("__invocation-ignored-args", po::value<int>(),
			"Number of args to ignore at beginning of argv");
}

void Command::printHelp(bool onError,
		std::vector<const char *> & invocation) const {
	if (!onError) {
		tkacz::say() << invocationString(invocation) << "— " << description
				<< "." << std::endl << std::endl;

		if (!longDesc.empty())
			tkacz::say() << longDesc << std::endl << std::endl;
	}

	for (uint i = 0; i < optionGroups.size(); i++) {
		if (hiddenOptionGroups.find(i) == hiddenOptionGroups.end()
				and optionGroups[i].options().size())
			tkacz::say() << optionGroups[i] << "\n";
	}

	if (!onError and !lastWords.empty())
		tkacz::say() << lastWords << std::endl << std::endl;
}

std::string Command::invocationString(std::vector<const char *> & invocation,
		std::string prefix, std::string suffix) const {
	std::string out;
	for (auto i : invocation) {
		out += i;
		out += " ";
		tkacz::debug_msg() << "invoc:" << i << "\n";
	}
	if (out.empty())
		return (out);
	return (prefix + out + suffix);

}
}
