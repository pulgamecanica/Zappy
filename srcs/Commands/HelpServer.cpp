//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>

#include "HelpServer.hpp"

namespace Zappy {
	HelpServer::HelpServer(): Command("help") {
	}


	HelpServer::~HelpServer() {
	}

	bool HelpServer::is_valid() const {
		return true; // It is always valid
	}
	
	void HelpServer::execute(Server & s) {
		std::cout << s.get_config().get("help") << std::endl;
	}

	std::ostream& operator<<(std::ostream& s, const HelpServer& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
