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

	const Tile&	Map::get_tile(int index) const {
		return get_tile(index_to_point(index));
	}

	Point Map::index_to_point(int index) const {
		return (Point(index / width_, index % width_));
	}

	int Map::point_to_index(const Point & p) const {
		return ((p.y() * width_) + p.x());
	}

	int Map::get_map_area() const {
		int base, height;
		
		base = brc_.x() - tlc_.x();
		height = brc_.y() - tlc_.y();
		return (base * height);
	}


	int Map::get_lowest_index() const {
		return (point_to_index(tlc_));
	}

	std::ostream& operator<<(std::ostream& s, const Map& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}

