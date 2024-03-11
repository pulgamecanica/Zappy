//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __HELPSERVER_HPP__
# define __HELPSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
	class HelpServer: public virtual Command {
		public:
			HelpServer();
			HelpServer(const HelpServer&) = default;
			virtual ~HelpServer();
			HelpServer&		operator= (const HelpServer&) = default; // const for safety... not super nesessary
			virtual bool	is_valid() const;
			virtual void	execute(Server & s, Client *p);
	};

	std::ostream&	operator<<(std::ostream&, const HelpServer&);
}

#endif

