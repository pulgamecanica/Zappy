//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __RIGHT_HPP__
# define __RIGHT_HPP__

#include <iostream>

#include "ClientCommand.hpp"

namespace Zappy {

  class Right: public ClientCommand {
    public:
      Right(GameEngine * trantor, Client * c);
      Right(const Right&) = delete;
      ~Right();
      Right&  operator= (const Right&) = delete; // const for safety... not super nesessary
      bool  is_valid() const;
      void  execute();
  };

  std::ostream& operator<<(std::ostream&, const Right&);
}
#endif

