//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __LEFT_HPP__
# define __LEFT_HPP__

#include <iostream>

#include "ClientCommand.hpp"

namespace Zappy {

  class Left: public ClientCommand {
  public:
    Left(GameEngine * trantor, Client * c);
    Left(const Left&) = delete;
    ~Left();
    Left& operator= (const Left&) = delete; // const for safety... not super nesessary
    bool  is_valid() const;
    void  execute();
};

std::ostream& operator<<(std::ostream&, const Left&);

}

#endif

