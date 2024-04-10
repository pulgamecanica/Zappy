//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "Commands/ServerCommands/StatusServer.hpp"

namespace Zappy {
  StatusServer::StatusServer(GameEngine *trantor): ServerCommand("status", trantor) {
  }

  StatusServer::~StatusServer() {
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
  void StatusServer::execute() {
    std::cout << GREEN << "Zappy v" << BLUE << Server::VERSION << ENDC
        << " - [" << BLUE << trantor_->get_creation_date() << ENDC << "]" << std::endl;
    std::cout << " * " << trantor_->get_config().get("total_players") << ":" << BLUE << trantor_->total_players() << ENDC << std::endl;
    std::cout << " * " << trantor_->get_config().get("total_spectators") << ":" << BLUE << trantor_->total_spectators() << ENDC << std::endl;
    std::cout << " * " << trantor_->get_config().get("server_life") << ":" << BLUE << trantor_->current_timestamp() << ENDC << "ms" << std::endl;
    // std::cout << trantor_->get_config().get_latency() << ":" << trantor_->latency() << std::endl;
    // std::cout << trantor_->get_languages_list_highlight_current() << std::endl;
  }

  std::ostream& operator<<(std::ostream& s, const StatusServer& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}

