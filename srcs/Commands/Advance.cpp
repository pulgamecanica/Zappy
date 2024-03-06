//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Advance.hpp"

Advance::Advance() {
	// TODO (default constructor)
}

Advance::Advance(const Advance& param) {
	// TODO (copy constructor)
	(void)param;
}

Advance::~Advance() {
	std::cout << "Advance" << " destroyed" << std::endl;
	// TODO (destructor)
}

Advance& Advance::operator= (const Advance& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const Advance& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

