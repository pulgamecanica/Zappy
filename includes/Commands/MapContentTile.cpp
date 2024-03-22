//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "MapContentTile.hpp"

MapContentTile::MapContentTile() {
	// TODO (default constructor)
}

MapContentTile::MapContentTile(const MapContentTile& param) {
	// TODO (copy constructor)
	(void)param;
}

MapContentTile::~MapContentTile() {
	std::cout << "MapContentTile" << " destroyed" << std::endl;
	// TODO (destructor)
}

MapContentTile& MapContentTile::operator= (const MapContentTile& param) {
	// TODO (Assignment operatior)
	// std::swap()
	(void)param;
	return (*this);
}

std::ostream& operator<<(std::ostream& s, const MapContentTile& param) {
	// s << param.CONST_METHOD()
	(void)param;
	return (s);
}

