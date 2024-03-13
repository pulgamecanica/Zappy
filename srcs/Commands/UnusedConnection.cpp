//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "UnusedConnection.hpp"

UnusedConnection::UnusedConnection() {
  // TODO (default constructor)
}

UnusedConnection::UnusedConnection(const UnusedConnection& param) {
  // TODO (copy constructor)
  (void)param;
}

UnusedConnection::~UnusedConnection() {
  std::cout << "UnusedConnection" << " destroyed" << std::endl;
  // TODO (destructor)
}

UnusedConnection& UnusedConnection::operator= (const UnusedConnection& param) {
  // TODO (Assignment operatior)
  // std::swap()
  (void)param;
  return (*this);
}

std::ostream& operator<<(std::ostream& s, const UnusedConnection& param) {
  // s << param.CONST_METHOD()
  (void)param;
  return (s);
}

