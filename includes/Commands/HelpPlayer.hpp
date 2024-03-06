//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __HELPPLAYER_HPP__
# define __HELPPLAYER_HPP__

#include <iostream>

class HelpPlayer {
	public:
		HelpPlayer();
		HelpPlayer(const HelpPlayer&);
		~HelpPlayer();
		HelpPlayer&	operator= (const HelpPlayer&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const HelpPlayer&);

#endif

