//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Incantation.hpp"

Incantation::Incantation() {
  // TODO (default constructor)
}

Incantation::Incantation(const Incantation& param) {
  // TODO (copy constructor)
  (void)param;
}

Incantation::~Incantation() {
  std::cout << "Incantation" << " destroyed" << std::endl;
  // TODO (destructor)
}

Incantation& Incantation::operator= (const Incantation& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const Incantation& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

