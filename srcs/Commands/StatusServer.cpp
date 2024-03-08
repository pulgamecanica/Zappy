//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "StatusServer.hpp"

#include "Zappy.inc"

namespace Zappy {
	StatusServer::StatusServer(): Command("status") {
		// TODO (default constructor)
	}

	StatusServer::~StatusServer() {
	}

	bool StatusServer::is_valid() const {
		return true; // It is always valid
	}
	
	/** Status should display
	 * Version, epoll
	 * Server life time
	 * Total players connected
	 * Total spectators
	 * Latency
	 * Current Language
	 * Languages available
	 */
	void StatusServer::execute(Server & s) {
		(void)s;
		std::cout << GREEN << "Zappy v" << BLUE << Server::VERSION << ENDC
				<< " - [" << BLUE << s.get_creation_date() << ENDC << "]" << std::endl;
		std::cout << " * " << s.get_config().get("total_players") << ":" << BLUE << s.total_players() << ENDC << std::endl;
		std::cout << " * " << s.get_config().get("total_spectators") << ":" << BLUE << s.total_spectators() << ENDC << std::endl;
		std::cout << " * " << s.get_config().get("server_life") << ":" << BLUE << s.current_timestamp() << ENDC << "s" << std::endl;
		// std::cout << s.get_config().get_latency() << ":" << s.latency() << std::endl;
		// std::cout << s.get_languages_list_highlight_current() << std::endl;
	}

	std::ostream& operator<<(std::ostream& s, const StatusServer& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

