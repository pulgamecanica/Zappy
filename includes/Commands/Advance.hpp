//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __ADVANCE_HPP__
# define __ADVANCE_HPP__

#include <iostream>

class Advance {
	public:
		Advance();
		Advance(const Advance&);
		~Advance();
		Advance&	operator= (const Advance&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const Advance&);

#endif

