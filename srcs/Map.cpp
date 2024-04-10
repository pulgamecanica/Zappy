//***************************//
//*Template by pulgamecanica*//
//***************************//

#include <sstream>

#include "Map.hpp"
#include "Tile.hpp"

namespace Zappy {
  //////////////////////////////// CONSTRUCTORS & DESTRUCTORS /////////////////////////////////////
	Map::Map(const Point & size): size_(size), tlc_(0, 0) {
		for (int i = 0; i < size.x() * size.y(); ++i) {
			map_.insert(Tile(index_to_point(i)));
		}
	}

	Map::~Map() {
		;
	}
  /////////////////////////////////////////////////////////////////////////////////////////////////

  /////////////////////////////////// CONST PUBLIC METHODS ////////////////////////////////////////
	int Map::get_lowest_index() const {
		return (point_to_index(tlc_));
	}

	int Map::get_height() const {
		return (size_.y() - tlc_.y());
	}

	int Map::get_map_area() const {
		return (get_width() * get_height());
	}
	
	const Tile& Map::get_tile(const Point &pos) const {
		if (!map_.contains(pos))
			throw std::runtime_error("Tile [" + std::string(pos) + "] is not in the map");
		return *map_.find(pos);
	}

	const Tile&	Map::get_tile(int index) const {
		return get_tile(index_to_point(index));
	}

	int Map::get_width() const {
		return (size_.x() - tlc_.x());
	}

	// A list with all the contents of the tile (not players)
	// std::string	Map::get_tile_content(const Tile & tile) const {
  //   std::stringstream ss;

	// 	ss << "Items: " << std::string(tile);
	// 	return (ss.str());
	// }

	Point Map::index_to_point(int index) const {
		return (Point(index / get_width(), index % get_width()));
	}

	int Map::point_to_index(const Point & p) const {
		return ((p.y() * get_width()) + p.x());
	}
  /////////////////////////////////////////////////////////////////////////////////////////////////

  ////////////////////////////////// CONST PROTECTED METHODS //////////////////////////////////////
	const Point Map::get_map_size() const {
		return (size_);
	}
  /////////////////////////////////////////////////////////////////////////////////////////////////

	std::ostream& operator<<(std::ostream& s, const Map& param) {
		// s << param.CONST_METHOD()
		(void)param;
		return (s);
	}
}
