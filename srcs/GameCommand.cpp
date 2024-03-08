//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "GameCommand.hpp"

GameCommand::GameCommand() {
	// TODO (default constructor)
}

GameCommand::GameCommand(const GameCommand& param) {
	// TODO (copy constructor)
	(void)param;
}

GameCommand::~GameCommand() {
	std::cout << "GameCommand" << " destroyed" << std::endl;
	// TODO (destructor)
}

GameCommand& GameCommand::operator= (const GameCommand& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const GameCommand& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

