//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Kick.hpp"

Kick::Kick() {
	// TODO (default constructor)
}

Kick::Kick(const Kick& param) {
	// TODO (copy constructor)
	(void)param;
}

Kick::~Kick() {
	std::cout << "Kick" << " destroyed" << std::endl;
	// TODO (destructor)
}

Kick& Kick::operator= (const Kick& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const Kick& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

