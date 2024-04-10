//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __STATUSSERVER_HPP__
# define __STATUSSERVER_HPP__

#include <iostream>

#include "ServerCommand.hpp"
#include "GameEngine.hpp"

namespace Zappy {

class StatusServer: public ServerCommand {
  public:
    StatusServer(GameEngine * trantor);
    StatusServer(const StatusServer&) = delete;
    StatusServer& operator= (const StatusServer&) = delete;
    ~StatusServer();
    void  execute();
};

std::ostream& operator<<(std::ostream&, const StatusServer&);
}

#endif

