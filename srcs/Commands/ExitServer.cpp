//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "ExitServer.hpp"

namespace Zappy {
  ExitServer::ExitServer(Server * s): Command("exit", s) {}

  ExitServer::~ExitServer() {}
  
  bool  ExitServer::is_valid() const { return true; }
  
  void  ExitServer::execute() {
    // Server Must be implemented
    s_->stop_server();
  }

  std::ostream& operator<<(std::ostream& s, const ExitServer& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}
