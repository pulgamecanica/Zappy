//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __HELPSERVER_HPP__
# define __HELPSERVER_HPP__

#include <iostream>

#include "ServerCommand.hpp"
#include "Server.hpp"

namespace Zappy {
  class HelpServer: public ServerCommand {
    public:
      HelpServer(GameEngine *trantor);
      HelpServer(const HelpServer&) = delete;
      HelpServer&   operator= (const HelpServer&) = delete;
      ~HelpServer();
      void  execute();
  };

  std::ostream& operator<<(std::ostream&, const HelpServer&);
}

#endif

