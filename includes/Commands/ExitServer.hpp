//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __EXITSERVER_HPP__
# define __EXITSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
  class ExitServer: public Command {
    public:
      ExitServer(Server * s);
      ExitServer(const ExitServer&) = default;
      ~ExitServer();
      ExitServer& operator= (const ExitServer&) = default; // const for safety... not super nesessary
      bool  is_valid() const;
      void  execute();
  };

  std::ostream& operator<<(std::ostream&, const ExitServer&);
}

#endif

