//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __MAP_HPP__
# define __MAP_HPP__

#include <iostream>
#include <set>

#include "Geometry/Point.hpp"
#include "Geometry/Direction.hpp"
// #include "Tile.hpp"

namespace Zappy {
	class Tile;

	class Map {
		public:
			Map(const Point & size);
			Map(const Map&) = default;
			~Map();
			Map&	operator= (const Map&) = default; // const for safety... not super nesessary
			const Tile&		get_tile(const Point &pos) const;			
			const Tile&		get_tile(int index) const;
			int point_to_index(const Point & p) const;
			Point index_to_point(int index) const;
			int get_lowest_index() const;			
			int get_map_area() const;
		protected:
			Point get_map_size() const;
      Point tlc_; // Top Left Corner
      Point brc_; // Bottom Right Corner
      std::set<Tile> map_;
      int width_;
	};
	std::ostream&	operator<<(std::ostream&, const Map&);
}
#endif

