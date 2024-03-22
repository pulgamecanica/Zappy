//***************************//
//*Template by pulgamecanica*//
//***************************//

#include "Map.hpp"
#include "Tile.hpp"

namespace Zappy {

	Map::Map(const Point & size): tlc_(0, 0), brc_(size), width_(size.x()) {
		for (int i = 0; i < size.x() * size.y(); ++i) {
			map_.insert(Tile(i, size.x()));
		}
	}

	Map::~Map() {
		// std::cout << "Map" << " destroyed" << std::endl;
		// TODO (destructor)
	}

	Point Map::get_map_size() const {
		return (Point(brc_.x() - tlc_.x(), brc_.y() - tlc_.y()));
	}

	const Tile& Map::get_tile(const Point &pos) const {
		if (!map_.contains(pos))
			throw std::runtime_error("Position [" + std::string(pos) + "] is not in the map");
		return *map_.find(pos);
	}

	std::ostream& operator<<(std::ostream& s, const Map& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

