//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __STATUSPLAYER_HPP__
# define __STATUSPLAYER_HPP__

#include <iostream>

class StatusPlayer {
	public:
		StatusPlayer();
		StatusPlayer(const StatusPlayer&);
		~StatusPlayer();
		StatusPlayer&	operator= (const StatusPlayer&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const StatusPlayer&);

#endif

