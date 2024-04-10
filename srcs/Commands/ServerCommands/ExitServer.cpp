//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/ServerCommands/ExitServer.hpp"

namespace Zappy {
  ExitServer::ExitServer(GameEngine * trantor): ServerCommand("exit", trantor) {}

  ExitServer::~ExitServer() {}
  
  void  ExitServer::execute() {
    trantor_->stop_server();
  }

  std::ostream& operator<<(std::ostream& s, const ExitServer& param) {
    (void)param;
    return (s);
  }
}
