//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TILE_HPP__
# define __TILE_HPP__

#include <iostream>
#include <map>

#include "Geometry/Point.hpp"
#include "Resource.hpp"

namespace Zappy {

	class Tile {
		public:
			static Point index_to_point(int i, int width);
			Tile(int i, int width);
			Tile(const Point& pos);
			Tile(const Tile&) = default;
			~Tile();
			void	add_new_resource(Resource res);
			Tile&	operator= (const Tile&) = default; // const for safety... not super nesessary
      bool	operator==(const Point&) const;// Needed in order to use find with a Point
			bool	operator== (const Tile&) const;
			bool	operator< (const Tile&) const;
			bool	operator> (const Tile&) const;
			inline int get_index(int width) const;
      explicit operator std::string() const;
			const Point & get_pos() const;
		private:
			const Point pos_;
			std::map<Resource::ResourceType, int> resources_;
	};

	std::ostream&	operator<<(std::ostream&, const Tile&);
}
#endif

