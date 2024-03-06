//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "HelpPlayer.hpp"

HelpPlayer::HelpPlayer() {
	// TODO (default constructor)
}

HelpPlayer::HelpPlayer(const HelpPlayer& param) {
	// TODO (copy constructor)
	(void)param;
}

HelpPlayer::~HelpPlayer() {
	std::cout << "HelpPlayer" << " destroyed" << std::endl;
	// TODO (destructor)
}

HelpPlayer& HelpPlayer::operator= (const HelpPlayer& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const HelpPlayer& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

