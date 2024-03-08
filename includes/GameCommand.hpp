//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __GAMECOMMAND_HPP__
# define __GAMECOMMAND_HPP__

#include <iostream>

class GameCommand {
	public:
		GameCommand();
		GameCommand(const GameCommand&);
		~GameCommand();
		GameCommand&	operator= (const GameCommand&); // const for safety... not super nesessary
};

std::ostream&	operator<<(std::ostream&, const GameCommand&);

#endif

