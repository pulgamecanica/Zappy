//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>

#include "HelpServer.hpp"

namespace Zappy {
	HelpServer::HelpServer(Server * s): Command("help", s) {
	}


	HelpServer::~HelpServer() {
	}

	bool HelpServer::is_valid() const {
		return true; // It is always valid
	}
	
	void HelpServer::execute() {
		std::cout << s_->get_config().get("help") << std::endl;
	}

	std::ostream& operator<<(std::ostream& s, const HelpServer& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
