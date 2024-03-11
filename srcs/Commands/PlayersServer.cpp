//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "PlayersServer.hpp"
#include "Client.hpp"

namespace Zappy {

	PlayersServer::PlayersServer(): Command("players") {
	}


	PlayersServer::~PlayersServer() {
		// std::cout << "PlayersServer" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	bool	PlayersServer::is_valid() const {
		return true;
	}

	void	PlayersServer::execute(Server & s, Client *client) {
		(void)client;
		const std::map<int, Client *> players = s.get_players();
		int i;
		std::cout << "#Players:" << BLUE << players.size() << ENDC << std::endl;
		i = 1;
		for (std::map<int, Client *>::const_iterator it = players.begin(); it != players.end(); ++it) {
			std::cout << " " << i << ". fd:" << BLUE << it->first << ENDC << " (" <<
				BLUE << it->second->uptime() << ENDC << "s)" << std::endl;	
			i++;
		}
		std::cout << std::endl; 	
	}

	std::ostream& operator<<(std::ostream& s, const PlayersServer& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

