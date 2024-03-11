//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "ExitServer.hpp"

namespace Zappy {
	ExitServer::ExitServer(): Command("exit") {}

	ExitServer::~ExitServer() {}
	
	bool	ExitServer::is_valid() const { return true; }
	
	void	ExitServer::execute(Server & s, Client * client) {
		(void)client;
		s.stop_server();
	}

	std::ostream& operator<<(std::ostream& s, const ExitServer& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
