//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __MAPCONTENTTILE_HPP__
# define __MAPCONTENTTILE_HPP__

#include <iostream>

class MapContentTile {
	public:
		MapContentTile();
		MapContentTile(const MapContentTile&);
		~MapContentTile();
		MapContentTile&	operator= (const MapContentTile&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const MapContentTile&);

#endif

