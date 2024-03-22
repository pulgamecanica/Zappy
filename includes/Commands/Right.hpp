//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __RIGHT_HPP__
# define __RIGHT_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "Player.hpp"

namespace Zappy {

  class Right: public ClientCommand {
    public:
      Right(GameEngine *trantor, Player *p);
      Right(const Right&) = delete;
      ~Right();
      Right&  operator= (const Right&) = delete; // const for safety... not super nesessary
      void  broadcast() const;
      bool  is_valid() const;
      void  execute();
      const std::string cmd_error() const;
    private:
      Player *player_;
  };

  std::ostream& operator<<(std::ostream&, const Right&);
}
#endif

