//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __BROADCAST_HPP__
# define __BROADCAST_HPP__

#include <iostream>

class Broadcast {
  public:
    Broadcast();
    Broadcast(const Broadcast&);
    ~Broadcast();
    Broadcast&  operator= (const Broadcast&); // const for safety... not super nesessary
};

std::ostream& operator<<(std::ostream&, const Broadcast&);

#endif

