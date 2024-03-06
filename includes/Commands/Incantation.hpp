//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __INCANTATION_HPP__
# define __INCANTATION_HPP__

#include <iostream>

class Incantation {
	public:
		Incantation();
		Incantation(const Incantation&);
		~Incantation();
		Incantation&	operator= (const Incantation&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const Incantation&);

#endif

