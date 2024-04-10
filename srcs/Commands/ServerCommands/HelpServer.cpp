//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>

#include "Commands/ServerCommands/HelpServer.hpp"

namespace Zappy {
  HelpServer::HelpServer(GameEngine *trantor): ServerCommand("help", trantor) {
  }


  HelpServer::~HelpServer() {
  }

  void HelpServer::execute() {
    std::cout << trantor_->get_config().get("help") << std::endl;
  }

  std::ostream& operator<<(std::ostream& s, const HelpServer& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}
