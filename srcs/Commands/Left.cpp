//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Left.hpp"

Left::Left() {
	// TODO (default constructor)
}

Left::Left(const Left& param) {
	// TODO (copy constructor)
	(void)param;
}

Left::~Left() {
	std::cout << "Left" << " destroyed" << std::endl;
	// TODO (destructor)
}

Left& Left::operator= (const Left& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const Left& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

