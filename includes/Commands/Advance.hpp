//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __ADVANCE_HPP__
# define __ADVANCE_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

namespace Zappy {

  class Advance: public ClientCommand {
    public:
      Advance(GameEngine *trantor, Player *p);
      Advance(const Advance&) = delete;
      ~Advance();
      Advance&  operator= (const Advance&) = delete; // const for safety... not super nesessary
      void  broadcast() const;
      bool  is_valid() const;
      void  execute();
      const std::string cmd_error() const;
    private:
      Player *player_;
  };

  std::ostream& operator<<(std::ostream&, const Advance&);
}
#endif

