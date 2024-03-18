//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Resource.hpp"

Resource::Resource() {
	// TODO (default constructor)
}

Resource::Resource(const Resource& param) {
	// TODO (copy constructor)
	(void)param;
}

Resource::~Resource() {
	std::cout << "Resource" << " destroyed" << std::endl;
	// TODO (destructor)
}

Resource& Resource::operator= (const Resource& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const Resource& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

