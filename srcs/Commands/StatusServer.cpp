//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Zappy.inc"

#include "Commands/StatusServer.hpp"

namespace Zappy {
  StatusServer::StatusServer(Server * s): Command("status", s) {
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
  void StatusServer::execute() {
    std::cout << GREEN << "Zappy v" << BLUE << Server::VERSION << ENDC
        << " - [" << BLUE << s_->get_creation_date() << ENDC << "]" << std::endl;
    std::cout << " * " << s_->get_config().get("total_players") << ":" << BLUE << s_->total_players() << ENDC << std::endl;
    std::cout << " * " << s_->get_config().get("total_spectators") << ":" << BLUE << s_->total_spectators() << ENDC << std::endl;
    std::cout << " * " << s_->get_config().get("server_life") << ":" << BLUE << s_->current_timestamp() << ENDC << "ms" << std::endl;
    // std::cout << s_->get_config().get_latency() << ":" << s_->latency() << std::endl;
    // std::cout << s_->get_languages_list_highlight_current() << std::endl;
  }

  std::ostream& operator<<(std::ostream& s, const StatusServer& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}

