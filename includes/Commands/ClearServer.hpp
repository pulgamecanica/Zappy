//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CLEARSERVER_HPP__
# define __CLEARSERVER_HPP__

#include <iostream>

class ClearServer {
	public:
		ClearServer();
		ClearServer(const ClearServer&);
		~ClearServer();
		ClearServer&	operator= (const ClearServer&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const ClearServer&);

#endif

