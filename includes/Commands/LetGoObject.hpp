//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __LETGOOBJECT_HPP__
# define __LETGOOBJECT_HPP__

#include <iostream>

class LetGoObject {
	public:
		LetGoObject();
		LetGoObject(const LetGoObject&);
		~LetGoObject();
		LetGoObject&	operator= (const LetGoObject&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const LetGoObject&);

#endif

