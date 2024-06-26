//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TEAMSNAMES_HPP__
# define __TEAMSNAMES_HPP__

#include <iostream>

#include "SpectatorClientCommand.hpp"
#include "Spectator.hpp"

namespace Zappy {

	class TeamsNames: public SpectatorClientCommand {
		public:
			TeamsNames(GameEngine * trantor, Spectator & spectator);
			TeamsNames(const TeamsNames&) = delete;
			~TeamsNames();
			TeamsNames&	operator= (const TeamsNames&) = delete; // const for safety... not super nesessary
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
	};

	std::ostream&	operator<<(std::ostream&, const TeamsNames&);
}

#endif

