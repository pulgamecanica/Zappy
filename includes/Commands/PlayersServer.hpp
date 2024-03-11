//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __PLAYERSSERVER_HPP__
# define __PLAYERSSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
	class PlayersServer: public virtual Command {
		public:
			PlayersServer();
			PlayersServer(const PlayersServer&) = default;
			virtual ~PlayersServer();
			PlayersServer&	operator= (const PlayersServer&) = default; // const for safety... not super nesessary
			virtual bool	is_valid() const;
			virtual void	execute(Server & s, Client *c);
	};

	std::ostream&	operator<<(std::ostream&, const PlayersServer&);
}
#endif

