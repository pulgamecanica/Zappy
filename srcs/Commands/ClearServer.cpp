//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "ClearServer.hpp"

ClearServer::ClearServer() {
	// TODO (default constructor)
}

ClearServer::ClearServer(const ClearServer& param) {
	// TODO (copy constructor)
	(void)param;
}

ClearServer::~ClearServer() {
	std::cout << "ClearServer" << " destroyed" << std::endl;
	// TODO (destructor)
}

ClearServer& ClearServer::operator= (const ClearServer& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const ClearServer& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

