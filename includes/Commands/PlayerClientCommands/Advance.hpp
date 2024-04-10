//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __ADVANCE_HPP__
# define __ADVANCE_HPP__

#include <iostream>

#include "PlayerClientCommand.hpp"
#include "GameEngine.hpp"
#include "Player.hpp"

namespace Zappy {

  class Advance: public PlayerClientCommand {
    public:
      // CONSTRUCTORS & DESTRUCTORS //
      Advance(GameEngine *trantor, Player *p);
      Advance(const Advance&) = delete;
      Advance&  operator= (const Advance&) = delete;
      ~Advance();
      // PUBLIC INHERITED VIRTUAL METHODS //
      void  broadcast() const;
      void  execute();
      const std::string cmd_error() const;
    private:
      Player *player_;
  };

  std::ostream& operator<<(std::ostream&, const Advance&);
}
#endif

