//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Tile.hpp"

Tile::Tile() {
	// TODO (default constructor)
}

Tile::Tile(const Tile& param) {
	// TODO (copy constructor)
	(void)param;
}

Tile::~Tile() {
	std::cout << "Tile" << " destroyed" << std::endl;
	// TODO (destructor)
}

Tile& Tile::operator= (const Tile& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const Tile& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

