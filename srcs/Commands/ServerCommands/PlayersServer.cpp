//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "Client.hpp"
#include "Commands/ServerCommands/PlayersServer.hpp"

namespace Zappy {

  PlayersServer::PlayersServer(GameEngine *trantor): ServerCommand("players", trantor) {
  }


  PlayersServer::~PlayersServer() {
  }

  void  PlayersServer::execute() {
    const std::map<int, Client *> players = trantor_->get_clients();
    int i;
    std::cout << "#Players:" << BLUE << players.size() << ENDC << std::endl;
    i = 1;
    for (std::map<int, Client *>::const_iterator it = players.begin(); it != players.end(); ++it) {
      std::cout << " " << i << ". fd:" << BLUE << it->first << ENDC << " (" <<
        BLUE << it->second->uptime() << ENDC << "ms)" << std::endl; 
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

