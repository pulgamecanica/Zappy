//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __STATUSSERVER_HPP__
# define __STATUSSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {

class StatusServer: public Command {
	public:
		StatusServer(Server * s);
		StatusServer(const StatusServer&) = default;
		~StatusServer();
		StatusServer&	operator= (const StatusServer&) = default; // const for safety... not super nesessary
		bool	is_valid() const;
		void	execute();
};

std::ostream&	operator<<(std::ostream&, const StatusServer&);
}

#endif

