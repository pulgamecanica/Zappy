//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "LetGoObject.hpp"

LetGoObject::LetGoObject() {
  // TODO (default constructor)
}

LetGoObject::LetGoObject(const LetGoObject& param) {
  // TODO (copy constructor)
  (void)param;
}

LetGoObject::~LetGoObject() {
  std::cout << "LetGoObject" << " destroyed" << std::endl;
  // TODO (destructor)
}

LetGoObject& LetGoObject::operator= (const LetGoObject& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const LetGoObject& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

