//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "StatusServer.hpp"

StatusServer::StatusServer() {
	// TODO (default constructor)
}

StatusServer::StatusServer(const StatusServer& param) {
	// TODO (copy constructor)
	(void)param;
}

StatusServer::~StatusServer() {
	std::cout << "StatusServer" << " destroyed" << std::endl;
	// TODO (destructor)
}

StatusServer& StatusServer::operator= (const StatusServer& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const StatusServer& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

