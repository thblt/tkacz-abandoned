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
	
	Command(const char * name, const char * description, const char * longdesc=NULL, const char * lastWords=NULL, bool hidden=false, bool allowUnregistered=false, bool autoHelp=true);
		
	virtual void run(po::variables_map & args, std::vector<std::string> & others, std::string invocation) const = 0;
	
	bool execute(int argc, char * argv [], std::string invocationPrefix="") const;
	virtual bool execute(std::vector<std::string> args, std::string invocationPrefix="") const;
	bool execute(std::string & cmdline, std::string invocationPrefix="") const;
	
	void fail(std::string msg) const;
	void printHelp(bool onError, std::string invocationPrefix="") const;

	const char
		*name,
		/** The standard description in command list */
		*description, 
		/** A longer description for command help */
		*longDesc, 
		/** A few words to end of the help message */
		*lastWords;
		
	const bool hidden = false,
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