//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __SEE_HPP__
# define __SEE_HPP__

#include <iostream>

class See {
  public:
    See();
    See(const See&);
    ~See();
    See&  operator= (const See&); // const for safety... not super nesessary
};

std::ostream& operator<<(std::ostream&, const See&);

#endif

