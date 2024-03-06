//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __STATUSSERVER_HPP__
# define __STATUSSERVER_HPP__

#include <iostream>

class StatusServer {
	public:
		StatusServer();
		StatusServer(const StatusServer&);
		~StatusServer();
		StatusServer&	operator= (const StatusServer&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const StatusServer&);

#endif

