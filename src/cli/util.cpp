#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace tzcli {

	po::options_description get_default_options_description() {
		po::options_description options("Basic options");
		
		options.add_options()
			("help,h", "Show help for this command.");
		
		return options;
		
}

}