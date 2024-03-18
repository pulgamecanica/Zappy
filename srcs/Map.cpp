//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Map.hpp"

namespace Zappy {

	Map::Map(const Point & size): tlc_(0, 0), brc_(size) {
	}

	Map::~Map() {
		std::cout << "Map" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	Point Map::get_map_size() const {
		return (Point(brc_.x() - tlc_.x(), brc_.y() - tlc_.y()));
	}


	std::ostream& operator<<(std::ostream& s, const Map& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

