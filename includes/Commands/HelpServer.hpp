//***************************//
//*Template by pulgamecanica*//
//***************************//

#ifndef __HELPSERVER_HPP__
# define __HELPSERVER_HPP__

#include <iostream>

#include "Command.hpp"
#include "Server.hpp"

namespace Zappy {
	class HelpServer: public Command {
		public:
			HelpServer(Server * s);
			HelpServer(const HelpServer&) = default;
			~HelpServer();
			HelpServer&		operator= (const HelpServer&) = default; // const for safety... not super nesessary
			bool	is_valid() const;
			void	execute();
	};

	std::ostream&	operator<<(std::ostream&, const HelpServer&);
}

#endif

