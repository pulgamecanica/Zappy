//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERS_HPP__
# define __PLAYERS_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"

namespace Zappy {
	class Players: public SpectatorClientCommand {
		public:
			Players(GameEngine * trantor, Spectator & spectator);
			Players(const Players&) = delete;
			~Players();
			Players&	operator= (const Players&) = delete; // const for safety... not super nesessary
			bool  is_valid() const;
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
	};

	std::ostream&	operator<<(std::ostream&, const Players&);
}

#endif

