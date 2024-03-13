//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Right.hpp"

Right::Right() {
  // TODO (default constructor)
}

Right::Right(const Right& param) {
  // TODO (copy constructor)
  (void)param;
}

Right::~Right() {
  std::cout << "Right" << " destroyed" << std::endl;
  // TODO (destructor)
}

Right& Right::operator= (const Right& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const Right& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

