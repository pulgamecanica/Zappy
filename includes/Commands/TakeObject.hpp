//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TAKEOBJECT_HPP__
# define __TAKEOBJECT_HPP__

#include <iostream>

class TakeObject {
  public:
    TakeObject();
    TakeObject(const TakeObject&);
    ~TakeObject();
    TakeObject& operator= (const TakeObject&); // const for safety... not super nesessary
};

std::ostream& operator<<(std::ostream&, const TakeObject&);

#endif

