//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __ADVANCE_HPP__
# define __ADVANCE_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "GameEngine.hpp"

namespace Zappy {

  class Advance: public ClientCommand {
    public:
      Advance(GameEngine * trantor, Client * c);
      Advance(const Advance&) = delete;
      ~Advance();
      Advance&  operator= (const Advance&) = delete; // const for safety... not super nesessary
      bool  is_valid() const;
      void  execute();
  };

  std::ostream& operator<<(std::ostream&, const Advance&);
}
#endif

