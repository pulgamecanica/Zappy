//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __RIGHT_HPP__
# define __RIGHT_HPP__

#include <iostream>

class Right {
	public:
		Right();
		Right(const Right&);
		~Right();
		Right&	operator= (const Right&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const Right&);

#endif

