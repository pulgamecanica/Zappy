//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/ClearServer.hpp"

namespace Zappy {

  ClearServer::ClearServer(): Command("clear", NULL) {
    // TODO (default constructor)
  }


  ClearServer::~ClearServer() {
    // std::cout << "ClearServer" << " destroyed" << std::endl;
    // TODO (destructor)
  }

  bool  ClearServer::is_valid() const {
    return true;
  };
  
  void  ClearServer::execute() {
    std::string ansi_clear_window_seq("\033[H\033[2J");
    write(1, ansi_clear_window_seq.c_str(), ansi_clear_window_seq.length());
  }


  std::ostream& operator<<(std::ostream& s, const ClearServer& param) {
    // s << param.CONST_METHOD()
    (void)param;
    return (s);
  }
}

