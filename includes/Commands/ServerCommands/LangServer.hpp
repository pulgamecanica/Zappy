//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __LANGSERVER_HPP__
# define __LANGSERVER_HPP__

#include <iostream>
#include <vector>

#include "ServerCommand.hpp"
#include "GameEngine.hpp"

namespace Zappy {
  class LangServer: public ServerCommand {
    public:
      LangServer(GameEngine *trantor, std::vector<std::string> & options);
      LangServer(const LangServer&) = delete;
      LangServer& operator= (const LangServer&) = delete; // const for safety... not super nesessary
      ~LangServer();
      void  execute();
    private:
      std::vector<std::string> options_;
  };

  std::ostream& operator<<(std::ostream&, const LangServer&);
}

#endif

