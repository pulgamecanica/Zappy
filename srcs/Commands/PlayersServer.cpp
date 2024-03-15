//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "Client.hpp"
#include "Commands/PlayersServer.hpp"

namespace Zappy {

  PlayersServer::PlayersServer(Server *s): Command("players", s) {
  }


  PlayersServer::~PlayersServer() {
    // std::cout << "PlayersServer" << " destroyed" << std::endl;
    // TODO (destructor)
  }

  bool  PlayersServer::is_valid() const {
    return true;
  }

  void  PlayersServer::execute() {
    const std::map<int, Client *> players = s_->get_clients();
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

