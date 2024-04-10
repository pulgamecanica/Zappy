//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __EXITSERVER_HPP__
# define __EXITSERVER_HPP__

#include <iostream>

#include "ServerCommand.hpp"
#include "GameEngine.hpp"

namespace Zappy {
  class ExitServer: public ServerCommand {
    public:
      ExitServer(GameEngine * trantor);
      ExitServer(const ExitServer&) = delete;
      ExitServer& operator= (const ExitServer&) = delete;
      ~ExitServer();
      void  execute();
  };

  std::ostream& operator<<(std::ostream&, const ExitServer&);
}

#endif

