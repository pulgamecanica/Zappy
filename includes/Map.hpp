//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __MAP_HPP__
# define __MAP_HPP__

#include <iostream>
#include <set>

#include "Geometry/Point.hpp"
#include "Geometry/Direction.hpp"

namespace Zappy {
	class Tile;

	class Map {
		public:
      // CONSTRUCTORS & DESTRUCTORS //
			Map(const Point & size);
			Map(const Map&) = default;
			~Map();
			Map&	operator= (const Map&) = default;
      // CONST PUBLIC METHODS //
			int 					get_lowest_index() const;			
			int 					get_height() const;
			int 					get_map_area() const;
			const Tile&		get_tile(const Point &pos) const;			
			const Tile&		get_tile(int index) const;
			int 					get_width() const;
			// std::string		get_tile_content(const Tile & tile) const;
			Point 				index_to_point(int index) const;
			int 					point_to_index(const Point & p) const;
		protected:
      // CONST PROTECTED METHODS //
			const Point get_map_size() const;
      // PROTECTED MEMBERS //
      std::set<Tile>	map_;
      Point 					size_;
      Point 					tlc_; // Top Left Corner
	};
	std::ostream&	operator<<(std::ostream&, const Map&);
}
#endif

