//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __UNUSEDCONNECTION_HPP__
# define __UNUSEDCONNECTION_HPP__

#include <iostream>

class UnusedConnection {
	public:
		UnusedConnection();
		UnusedConnection(const UnusedConnection&);
		~UnusedConnection();
		UnusedConnection&	operator= (const UnusedConnection&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const UnusedConnection&);

#endif

