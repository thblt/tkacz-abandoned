#pragma once

#include <map>
#include <set>
#include <vector>
#include <string>

#include <boost/program_options.hpp>

namespace tkacz {
	
class Command {
public:

    enum class StandardOptionGroups : int {
        Basic = 0,
        Advanced = 1,
        Positional = 2,
        Hidden = 3
    };

    Command(const void (*callback)(boost::program_options::variables_map), bool metacommand=false);
    Command(bool metacommand) : Command(nullptr, metacommand) {}
    Command() : Command(nullptr, true) {}

    void addSubcommand(const char * name, Command * command);

    void printHelp(std::vector<std::string> invocation, std::string errorMsg="") const ;

    void initialize();

	bool execute(int argc, char * argv[]) const ;
	bool execute(std::string cmdline) const ;
    bool execute(std::vector<std::string> & args, std::vector<std::string> & invocation ) const ;

    std::string description,
    longDesc,
    lastWords;

    int addOptionGroup(const char * name, bool hidden=false) const ;

    void addOption(int group, const char * name, const boost::program_options::value_semantic * sem, const char * desc);
    void addOption(int group, const char * name, const char * desc);
    void addBasicOption(const char * name, const boost::program_options::value_semantic * sem, const char * desc);
    void addBasicOption(const char * name, const char * desc);
    void addAdvancedOption(const char * name, const boost::program_options::value_semantic * sem, const char * desc);
    void addAdvancedOption(const char * name, const char * desc);
    void addHiddenOption(const char * name, const boost::program_options::value_semantic * sem, const char * desc);
    void addHiddenOption(const char * name, const char * desc);
    void addPositionalArg(const char * name, int max, const char * desc="",
                          bool createUnderlying=true);
    void addPositionalArg(const char * name, const boost::program_options::value_semantic * sem, int max,
                          const char * desc="", bool createUnderlying=true);


protected:

    inline std::string invocationString(std::vector<std::string> & invocation,
                                        std::string prefix="", std::string suffix="") const;

    std::vector<boost::program_options::options_description> optionGroups = {
        { "Basic options" },
        { "Advanced options" },
        { "(Positional placeholders)" },
        { "Hidden options" }
    };
    boost::program_options::positional_options_description positionalArgs;

    std::set<int> hiddenOptionGroups { (int) StandardOptionGroups::Positional, (int) StandardOptionGroups::Hidden };

    std::map<std::string,Command*> subcommands;

    const void (*callback)(boost::program_options::variables_map) = nullptr;

    const bool metacommand;

};
	
}