//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/Fork.hpp"

Fork::Fork() {
  // TODO (default constructor)
}

Fork::Fork(const Fork& param) {
  // TODO (copy constructor)
  (void)param;
}

Fork::~Fork() {
  std::cout << "Fork" << " destroyed" << std::endl;
  // TODO (destructor)
}

Fork& Fork::operator= (const Fork& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const Fork& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

