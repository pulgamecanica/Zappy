//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __STATUSSERVER_HPP__
# define __STATUSSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {

class StatusServer: public virtual Command {
	public:
		StatusServer();
		StatusServer(const StatusServer&) = default;
		~StatusServer();
		StatusServer&	operator= (const StatusServer&) = default; // const for safety... not super nesessary
		virtual bool	is_valid() const;
		virtual void	execute(Server & s, Client *p);
};

std::ostream&	operator<<(std::ostream&, const StatusServer&);
}

#endif

