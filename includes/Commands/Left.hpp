//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __LEFT_HPP__
# define __LEFT_HPP__

#include <iostream>

class Left {
	public:
		Left();
		Left(const Left&);
		~Left();
		Left&	operator= (const Left&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const Left&);

#endif

