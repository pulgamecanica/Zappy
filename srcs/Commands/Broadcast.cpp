//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/Broadcast.hpp"

Broadcast::Broadcast() {
  // TODO (default constructor)
}

Broadcast::Broadcast(const Broadcast& param) {
  // TODO (copy constructor)
  (void)param;
}

Broadcast::~Broadcast() {
  std::cout << "Broadcast" << " destroyed" << std::endl;
  // TODO (destructor)
}

Broadcast& Broadcast::operator= (const Broadcast& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const Broadcast& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

