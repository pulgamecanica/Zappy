//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "TakeObject.hpp"

TakeObject::TakeObject() {
  // TODO (default constructor)
}

TakeObject::TakeObject(const TakeObject& param) {
  // TODO (copy constructor)
  (void)param;
}

TakeObject::~TakeObject() {
  std::cout << "TakeObject" << " destroyed" << std::endl;
  // TODO (destructor)
}

TakeObject& TakeObject::operator= (const TakeObject& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const TakeObject& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

