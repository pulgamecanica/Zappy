//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __LEFT_HPP__
# define __LEFT_HPP__

#include <iostream>

#include "PlayerClientCommand.hpp"
#include "Player.hpp"

namespace Zappy {

  class Left: public PlayerClientCommand {
    public:
      Left(GameEngine *trantor, Player *p);
      Left(const Left&) = delete;
      ~Left();
      Left& operator= (const Left&) = delete; // const for safety... not super nesessary
      void  broadcast() const;
      bool  is_valid() const;
      void  execute();
      const std::string cmd_error() const;
    private:
      Player *player_;
  };

  std::ostream& operator<<(std::ostream&, const Left&);

}

#endif

