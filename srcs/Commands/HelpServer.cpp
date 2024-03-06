//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>

#include "HelpServer.hpp"
#include "Zappy.inc"

namespace Zappy {
	HelpServer::HelpServer(): Command("help", false) {
	}


	HelpServer::~HelpServer() {
	}

	bool HelpServer::is_valid() const {
		return true;
	}
	
	const std::string HelpServer::get_output() const {
		std::stringstream ss;

		ss << BLUE << "help" << ENDC << " - Display all the available commands" << std::endl;
		const std::string str(ss.str());
		return (str);
	};


	std::ostream& operator<<(std::ostream& s, const HelpServer& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
