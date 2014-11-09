#include <boost/program_options.hpp>

namespace po = boost::program_options;

namespace tzcli {
	po::options_description get_default_options_description();
	bool process_common_options(po::variables_map vm);
}