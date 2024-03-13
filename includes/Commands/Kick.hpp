//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __KICK_HPP__
# define __KICK_HPP__

#include <iostream>

class Kick {
  public:
    Kick();
    Kick(const Kick&);
    ~Kick();
    Kick& operator= (const Kick&); // const for safety... not super nesessary
};

std::ostream& operator<<(std::ostream&, const Kick&);

#endif

