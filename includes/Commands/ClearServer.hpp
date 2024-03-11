//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __CLEARSERVER_HPP__
# define __CLEARSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
	class ClearServer: public virtual Command {
		public:
			ClearServer();
			ClearServer(const ClearServer&) = default;
			virtual ~ClearServer();
			ClearServer&	operator= (const ClearServer&) = default; // const for safety... not super nesessary
			virtual bool	is_valid() const;
			virtual void	execute(Server & s, Client *p);
	};

	std::ostream&	operator<<(std::ostream&, const ClearServer&);
}

#endif

