//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __TEAMSNAMES_HPP__
# define __TEAMSNAMES_HPP__

#include <iostream>

#include "ClientCommand.hpp"
#include "Spectator.hpp"

namespace Zappy {

	class TeamsNames: public ClientCommand {
		public:
			TeamsNames(GameEngine * trantor, Spectator & spectator);
			TeamsNames(const TeamsNames&) = delete;
			~TeamsNames();
			TeamsNames&	operator= (const TeamsNames&) = delete; // const for safety... not super nesessary
			bool  is_valid() const;
	    void  execute();
			const std::string cmd_error() const;
		private:
			Spectator & spectator_;
	};

	std::ostream&	operator<<(std::ostream&, const TeamsNames&);
}

#endif

