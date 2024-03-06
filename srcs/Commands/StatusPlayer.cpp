//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "StatusPlayer.hpp"

StatusPlayer::StatusPlayer() {
	// TODO (default constructor)
}

StatusPlayer::StatusPlayer(const StatusPlayer& param) {
	// TODO (copy constructor)
	(void)param;
}

StatusPlayer::~StatusPlayer() {
	std::cout << "StatusPlayer" << " destroyed" << std::endl;
	// TODO (destructor)
}

StatusPlayer& StatusPlayer::operator= (const StatusPlayer& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const StatusPlayer& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

