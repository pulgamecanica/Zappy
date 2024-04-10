//***************************//
//*Template by pulgamecanica*//
//***************************//

extern "C" {
  #include <unistd.h>
}

#include "Commands/ServerCommands/ClearServer.hpp"

namespace Zappy {

  ClearServer::ClearServer(): ServerCommand("clear", nullptr) {
  }


  ClearServer::~ClearServer() {
  }
  
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

