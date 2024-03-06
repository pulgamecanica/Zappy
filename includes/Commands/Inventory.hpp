//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __INVENTORY_HPP__
# define __INVENTORY_HPP__

#include <iostream>

class Inventory {
	public:
		Inventory();
		Inventory(const Inventory&);
		~Inventory();
		Inventory&	operator= (const Inventory&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const Inventory&);

#endif

