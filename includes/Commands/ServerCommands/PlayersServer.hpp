//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERSSERVER_HPP__
# define __PLAYERSSERVER_HPP__

#include <iostream>

#include "ServerCommand.hpp"
#include "GameEngine.hpp"

namespace Zappy {
  class PlayersServer: public ServerCommand {
    public:
      PlayersServer(GameEngine *trantor);
      PlayersServer(const PlayersServer&) = default;
      ~PlayersServer();
      PlayersServer&  operator= (const PlayersServer&) = default; // const for safety... not super nesessary
      void  execute();
  };

  std::ostream& operator<<(std::ostream&, const PlayersServer&);
}
#endif

