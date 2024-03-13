//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERSSERVER_HPP__
# define __PLAYERSSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
	class PlayersServer: public Command {
		public:
			PlayersServer(Server *s);
			PlayersServer(const PlayersServer&) = default;
			~PlayersServer();
			PlayersServer&	operator= (const PlayersServer&) = default; // const for safety... not super nesessary
			bool	is_valid() const;
			void	execute();
	};

	std::ostream&	operator<<(std::ostream&, const PlayersServer&);
}
#endif

