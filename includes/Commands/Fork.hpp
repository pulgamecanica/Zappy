//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __FORK_HPP__
# define __FORK_HPP__

#include <iostream>

class Fork {
  public:
    Fork();
    Fork(const Fork&);
    ~Fork();
    Fork& operator= (const Fork&); // const for safety... not super nesessary
};

std::ostream& operator<<(std::ostream&, const Fork&);

#endif

