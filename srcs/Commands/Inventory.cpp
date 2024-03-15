//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Commands/Inventory.hpp"

Inventory::Inventory() {
  // TODO (default constructor)
}

Inventory::Inventory(const Inventory& param) {
  // TODO (copy constructor)
  (void)param;
}

Inventory::~Inventory() {
  std::cout << "Inventory" << " destroyed" << std::endl;
  // TODO (destructor)
}

Inventory& Inventory::operator= (const Inventory& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const Inventory& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

