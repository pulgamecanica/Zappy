//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __MAP_HPP__
# define __MAP_HPP__

#include <iostream>

#include "Geometry/Point.hpp"
#include "Geometry/Direction.hpp"

namespace Zappy {
	class Map {
		public:
			Map(const Point & size);
			Map(const Map&) = default;
			~Map();
			Map&	operator= (const Map&) = default; // const for safety... not super nesessary
			// std::vector<Tile> tiles_;
			// resize(enum Orientation orientation);
		protected:
			Point get_map_size() const;
      // Point	map_size_;
      Point tlc_; // Top Left Corner
      Point brc_; // Bottom Right Corner
	};
	std::ostream&	operator<<(std::ostream&, const Map&);
}
#endif

