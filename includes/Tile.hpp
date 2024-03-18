//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TILE_HPP__
# define __TILE_HPP__

#include <iostream>

class Tile {
	public:
		Tile();
		Tile(const Tile&);
		~Tile();
		Tile&	operator= (const Tile&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const Tile&);

#endif

