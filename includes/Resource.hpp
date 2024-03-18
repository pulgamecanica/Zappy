//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __RESOURCE_HPP__
# define __RESOURCE_HPP__

#include <iostream>

class Resource {
	public:
		Resource();
		Resource(const Resource&);
		~Resource();
		Resource&	operator= (const Resource&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const Resource&);

#endif

