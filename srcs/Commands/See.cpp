//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/See.hpp"

See::See() {
  // TODO (default constructor)
}

See::See(const See& param) {
  // TODO (copy constructor)
  (void)param;
}

See::~See() {
  std::cout << "See" << " destroyed" << std::endl;
  // TODO (destructor)
}

See& See::operator= (const See& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const See& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

