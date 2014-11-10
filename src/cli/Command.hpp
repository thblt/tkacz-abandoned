#pragma once

#include <set>
#include <string>
#include <vector>

#include <boost/program_options.hpp> // Can't forward since optionGroups are initialized in this .hpp

#include <Tkacz.hpp>

namespace po = boost::program_options;

namespace tzcli {

class Command {
public:
	
	
		
	virtual void run(po::variables_map & args, std::vector<std::string> & others, std::vector<const char *> & invocation) const = 0;
	
	bool execute(int argc, char * argv [], std::vector<const char *> & invocation) const;
	virtual bool execute(std::vector<std::string> args, std::vector<const char *> & invocation) const;
	bool execute(std::string & cmdline, std::vector<const char *> & invocation) const;
	
	void printHelp(bool onError, std::vector<const char *> & invocation) const;

	// Public options

	std::string
		/** The standard description in command list */
		description, 
		/** A longer description for command help */
		longDesc, 
		/** A few words to end of the help message */
		lastWords;
		
	bool 
		hidden 			  = false,
		allowUnregistered = false,
		autoHelp          = true;
		
protected:
	int & addOptionGroup(std::string desc, bool hidden=false);

	void addBasicOption(const char * name, const po::value_semantic * sem, const char * desc);
	void addBasicOption(const char * name, const char * desc);
	void addAdvancedOption(const char * name, const po::value_semantic * sem, const char * desc);
	void addAdvancedOption(const char * name, const char * desc);
	void addHiddenOption(const char * name, const po::value_semantic * sem, const char * desc);
	void addHiddenOption(const char * name, const char * desc);
	
	void addOption(int group, const char * name, const po::value_semantic * sem, const char * desc);
	void addOption(int group, const char * name, const char * desc);
	
	void addPositionalArg(const char * name, const po::value_semantic * sem, int max, bool createUnderlying=true);
	void addPositionalArg(const char * name, int max, bool createUnderlying=true);
	
	void initialize();
	
	std::string invocationString(std::vector<const char *> invocation, std::string prefix="", std::string suffix="") const;

	po::positional_options_description positionalArgs;
	
	std::vector<po::options_description> optionGroups = {
		{ "Basic Options" },           // 0
		{ "Advanced options" },        // 1
		{ "Positional placeholders" }, // 2
		{ "Hidden options" }           // 3
	};
	
	std::set<int> hiddenOptionGroups {2, 3};
		
};

}